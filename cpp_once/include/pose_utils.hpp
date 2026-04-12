#pragma once
#include <opencv2/opencv.hpp>
#include <array>

// 4x4 位姿矩阵（行主序，CV_64F）
using Pose4x4 = cv::Mat;

// 打印位姿到终端（平移、距离、欧拉角RPY、四元数xyzw）
void printPose(const Pose4x4& pose);

// 在图像上叠加位姿文字（Dist + RPY）
void drawPoseText(cv::Mat& img_bgr, const Pose4x4& pose);

// 将位姿结果图保存到 results/ 目录，文件名含时间戳
// 返回保存路径
std::string savePoseImage(const cv::Mat& vis_bgr,
                          const std::string& results_dir);
