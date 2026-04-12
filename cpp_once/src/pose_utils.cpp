#include "pose_utils.hpp"
#include <cmath>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

// ── 旋转矩阵 → 欧拉角 RPY (rad，xyz顺序) ────────────────────────────────────
static cv::Vec3d rotMatToRPY(const cv::Mat& R)
{
    // R 是 3x3 CV_64F
    double sy = std::sqrt(R.at<double>(0,0)*R.at<double>(0,0) +
                          R.at<double>(1,0)*R.at<double>(1,0));
    bool singular = sy < 1e-6;
    double rx, ry, rz;
    if (!singular) {
        rx = std::atan2( R.at<double>(2,1), R.at<double>(2,2));
        ry = std::atan2(-R.at<double>(2,0), sy);
        rz = std::atan2( R.at<double>(1,0), R.at<double>(0,0));
    } else {
        rx = std::atan2(-R.at<double>(1,2), R.at<double>(1,1));
        ry = std::atan2(-R.at<double>(2,0), sy);
        rz = 0;
    }
    return {rx, ry, rz};
}

// ── 旋转矩阵 → 四元数 xyzw ───────────────────────────────────────────────────
static cv::Vec4d rotMatToQuat(const cv::Mat& R)
{
    double trace = R.at<double>(0,0) + R.at<double>(1,1) + R.at<double>(2,2);
    double qw, qx, qy, qz;
    if (trace > 0) {
        double s = 0.5 / std::sqrt(trace + 1.0);
        qw = 0.25 / s;
        qx = (R.at<double>(2,1) - R.at<double>(1,2)) * s;
        qy = (R.at<double>(0,2) - R.at<double>(2,0)) * s;
        qz = (R.at<double>(1,0) - R.at<double>(0,1)) * s;
    } else if (R.at<double>(0,0) > R.at<double>(1,1) && R.at<double>(0,0) > R.at<double>(2,2)) {
        double s = 2.0 * std::sqrt(1.0 + R.at<double>(0,0) - R.at<double>(1,1) - R.at<double>(2,2));
        qw = (R.at<double>(2,1) - R.at<double>(1,2)) / s;
        qx = 0.25 * s;
        qy = (R.at<double>(0,1) + R.at<double>(1,0)) / s;
        qz = (R.at<double>(0,2) + R.at<double>(2,0)) / s;
    } else if (R.at<double>(1,1) > R.at<double>(2,2)) {
        double s = 2.0 * std::sqrt(1.0 + R.at<double>(1,1) - R.at<double>(0,0) - R.at<double>(2,2));
        qw = (R.at<double>(0,2) - R.at<double>(2,0)) / s;
        qx = (R.at<double>(0,1) + R.at<double>(1,0)) / s;
        qy = 0.25 * s;
        qz = (R.at<double>(1,2) + R.at<double>(2,1)) / s;
    } else {
        double s = 2.0 * std::sqrt(1.0 + R.at<double>(2,2) - R.at<double>(0,0) - R.at<double>(1,1));
        qw = (R.at<double>(1,0) - R.at<double>(0,1)) / s;
        qx = (R.at<double>(0,2) + R.at<double>(2,0)) / s;
        qy = (R.at<double>(1,2) + R.at<double>(2,1)) / s;
        qz = 0.25 * s;
    }
    return {qx, qy, qz, qw};  // xyzw
}

// ─────────────────────────────────────────────────────────────────────────────
void printPose(const Pose4x4& pose)
{
    cv::Mat t = pose(cv::Rect(3, 0, 1, 3));   // 3x1
    cv::Mat R = pose(cv::Rect(0, 0, 3, 3));   // 3x3

    double dist = cv::norm(t);
    auto rpy  = rotMatToRPY(R);
    auto quat = rotMatToQuat(R);
    const double r2d = 180.0 / M_PI;

    std::cout << "\n========== 位姿结果 ==========\n";
    std::cout << "4x4 变换矩阵 (ob_in_cam):\n" << pose << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n平移 (x, y, z) [m]: "
              << t.at<double>(0) << "  "
              << t.at<double>(1) << "  "
              << t.at<double>(2) << "\n";
    std::cout << "距离相机          : " << dist << " m\n";
    std::cout << std::setprecision(2);
    std::cout << "欧拉角 RPY [deg]  : "
              << rpy[0]*r2d << "  " << rpy[1]*r2d << "  " << rpy[2]*r2d << "\n";
    std::cout << std::setprecision(4);
    std::cout << "四元数 xyzw       : "
              << quat[0] << "  " << quat[1] << "  "
              << quat[2] << "  " << quat[3] << "\n";
    std::cout << "==============================\n\n";
}

// ─────────────────────────────────────────────────────────────────────────────
void drawPoseText(cv::Mat& img_bgr, const Pose4x4& pose)
{
    cv::Mat t = pose(cv::Rect(3, 0, 1, 3));
    cv::Mat R = pose(cv::Rect(0, 0, 3, 3));
    double dist = cv::norm(t);
    auto rpy = rotMatToRPY(R);
    const double r2d = 180.0 / M_PI;

    auto fmt = [](double v, int prec=1) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(prec) << v;
        return ss.str();
    };

    std::vector<std::string> lines = {
        "Dist: " + fmt(dist, 3) + " m",
        "RPY: " + fmt(rpy[0]*r2d) + " " + fmt(rpy[1]*r2d) + " " + fmt(rpy[2]*r2d) + " deg"
    };

    int font = cv::FONT_HERSHEY_SIMPLEX;
    for (int i = 0; i < (int)lines.size(); ++i) {
        int y = 25 + i * 22;
        cv::putText(img_bgr, lines[i], {10, y}, font, 0.55, {0,0,0},       3, cv::LINE_AA);
        cv::putText(img_bgr, lines[i], {10, y}, font, 0.55, {255,255,255}, 1, cv::LINE_AA);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
std::string savePoseImage(const cv::Mat& vis_bgr, const std::string& results_dir)
{
    // 确保目录存在
    mkdir(results_dir.c_str(), 0755);

    std::time_t now = std::time(nullptr);
    std::tm* tm_info = std::localtime(&now);
    std::ostringstream ss;
    ss << results_dir << "/pose_"
       << std::put_time(tm_info, "%Y%m%d_%H%M%S") << ".png";
    std::string path = ss.str();
    cv::imwrite(path, vis_bgr);
    return path;
}
