#include "pose_utils.hpp"
#include <cmath>//数学函数
#include <ctime>//时间函数
#include <iomanip>//格式化输出
#include <sstream>//哟字符串六，用于拼接文件名字符串
#include <iostream>
#include <sys/stat.h>//linux系统调用，mkdir创建目录，确保results文件夹存在

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

// 打印输出欧拉角和四元数─────────────────────────────────────────────────────────────────────────────
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

// 在保存图片上显示rpy，xyzw─────────────────────────────────────────────────────────────────────────────
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

// 图片保存到results─────────────────────────────────────────────────────────────────────────────
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

// 绘制物体坐标系三轴────────────────────────────────────────────────────────────
void drawAxes(cv::Mat& img_bgr, const Pose4x4& pose, const cv::Mat& K, double axis_len)
{
    // 物体坐标系原点和三轴端点（物体坐标系下）
    cv::Mat pts(4, 3, CV_64F);
    pts.row(0) = (cv::Mat_<double>(1,3) << 0, 0, 0);           // 原点
    pts.row(1) = (cv::Mat_<double>(1,3) << axis_len, 0, 0);    // X 轴 红
    pts.row(2) = (cv::Mat_<double>(1,3) << 0, axis_len, 0);    // Y 轴 绿
    pts.row(3) = (cv::Mat_<double>(1,3) << 0, 0, axis_len);    // Z 轴 蓝

    cv::Mat R = pose(cv::Rect(0, 0, 3, 3));
    cv::Mat t = pose(cv::Rect(3, 0, 1, 3));
    double fx = K.at<double>(0,0), fy = K.at<double>(1,1);
    double cx = K.at<double>(0,2), cy = K.at<double>(1,2);

    // 将每个点变换到相机坐标系再投影
    auto project = [&](int i) -> cv::Point {
        cv::Mat p = R * pts.row(i).t() + t;  // 3x1
        double x = p.at<double>(0), y = p.at<double>(1), z = p.at<double>(2);
        return {(int)(fx * x / z + cx), (int)(fy * y / z + cy)};
    };

    cv::Point o  = project(0);
    cv::Point px = project(1);
    cv::Point py = project(2);
    cv::Point pz = project(3);

    cv::arrowedLine(img_bgr, o, px, {0,   0,   255}, 2, cv::LINE_AA, 0, 0.2); // X 红
    cv::arrowedLine(img_bgr, o, py, {0,   255, 0  }, 2, cv::LINE_AA, 0, 0.2); // Y 绿
    cv::arrowedLine(img_bgr, o, pz, {255, 0,   0  }, 2, cv::LINE_AA, 0, 0.2); // Z 蓝
}
