#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>

struct Detection {
    cv::Rect  bbox;       // 原图坐标
    float     conf;
    cv::Mat   mask;       // CV_8UC1, 原图尺寸, 0/255
};

class YoloSeg {
public:
    YoloSeg(const std::string& model_path,
            float conf_thresh = 0.35f,
            float iou_thresh  = 0.45f,
            int   input_size  = 640);

    // 输入 RGB uint8，返回检测结果列表
    std::vector<Detection> infer(const cv::Mat& img_rgb);

private:
    // 预处理：letterbox → float32 NCHW blob
    cv::Mat preprocess(const cv::Mat& img_rgb,
                       float& scale, int& pad_x, int& pad_y);

    // 后处理：解析 output0/output1，NMS，生成 mask
    std::vector<Detection> postprocess(
        const float* out0, const float* out1,
        int orig_h, int orig_w,
        float scale, int pad_x, int pad_y);

    // NMS，返回保留的索引
    std::vector<int> nms(const std::vector<cv::Rect2f>& boxes,
                         const std::vector<float>& scores);

    Ort::Env            env_;
    Ort::Session        session_{nullptr};
    Ort::MemoryInfo     mem_info_{nullptr};

    float conf_thresh_;
    float iou_thresh_;
    int   input_size_;

    // output0: [1,37,8400]  output1: [1,32,160,160]
    static constexpr int NUM_ANCHORS   = 8400;
    static constexpr int NUM_PROTO_CH  = 32;
    static constexpr int PROTO_HW      = 160;
};
