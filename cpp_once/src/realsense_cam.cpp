#include "realsense_cam.hpp"
#include <stdexcept>
#include <iostream>

RealSenseCam::RealSenseCam(int width, int height, int fps)
    : align_(RS2_STREAM_COLOR), width_(width), height_(height)
{
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_RGB8, fps);
    cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16,  fps);

    rs2::pipeline_profile profile = pipeline_.start(cfg);

    // 深度比例尺
    auto sensor = profile.get_device().first<rs2::depth_sensor>();
    depth_scale_ = sensor.get_depth_scale();

    // 相机内参
    auto stream = profile.get_stream(RS2_STREAM_COLOR)
                         .as<rs2::video_stream_profile>();
    intr_ = stream.get_intrinsics();

    std::cout << "[RealSense] 已启动  " << width << "x" << height
              << "@" << fps << "fps  depth_scale=" << depth_scale_ << "\n";
}

RealSenseCam::~RealSenseCam()
{
    pipeline_.stop();
}

cv::Mat RealSenseCam::getK() const
{
    cv::Mat K = cv::Mat::eye(3, 3, CV_64F);
    K.at<double>(0,0) = intr_.fx;
    K.at<double>(1,1) = intr_.fy;
    K.at<double>(0,2) = intr_.ppx;
    K.at<double>(1,2) = intr_.ppy;
    return K;
}

float RealSenseCam::getDepthScale() const { return depth_scale_; }

FramePair RealSenseCam::waitForFrame()
{
    rs2::frameset frames = pipeline_.wait_for_frames();
    frames = align_.process(frames);

    rs2::video_frame color_frame = frames.get_color_frame();
    rs2::depth_frame depth_frame = frames.get_depth_frame();

    FramePair fp;
    // color: RGB8 → cv::Mat
    fp.color_rgb = cv::Mat(height_, width_, CV_8UC3,
                           (void*)color_frame.get_data()).clone();
    // depth: Z16 → cv::Mat
    fp.depth_raw = cv::Mat(height_, width_, CV_16UC1,
                           (void*)depth_frame.get_data()).clone();
    return fp;
}
