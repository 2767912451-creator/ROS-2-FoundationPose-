#pragma once
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

struct FramePair {
    cv::Mat color_rgb;   // CV_8UC3 RGB
    cv::Mat depth_raw;   // CV_16UC1 原始深度
};

class RealSenseCam {
public:
    RealSenseCam(int width = 640, int height = 480, int fps = 30);
    ~RealSenseCam();

    // 获取相机内参矩阵 3x3 CV_64F
    cv::Mat getK() const;
    float   getDepthScale() const;

    // 阻塞等待一帧，返回对齐后的彩色+深度
    FramePair waitForFrame();

private:
    rs2::pipeline pipeline_;
    rs2::align    align_;
    float         depth_scale_{0.f};
    rs2_intrinsics intr_{};
    int width_, height_;
};
