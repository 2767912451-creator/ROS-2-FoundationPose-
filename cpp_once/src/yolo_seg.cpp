#include "yolo_seg.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iostream>

// ─────────────────────────────────────────────────────────────────────────────
YoloSeg::YoloSeg(const std::string& model_path,
                 float conf_thresh, float iou_thresh, int input_size)
    : env_(ORT_LOGGING_LEVEL_WARNING, "YoloSeg"),
      conf_thresh_(conf_thresh),
      iou_thresh_(iou_thresh),
      input_size_(input_size)
{
    Ort::SessionOptions opts;
    opts.SetIntraOpNumThreads(1);
    opts.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

    // 尝试启用 CUDA EP
    OrtCUDAProviderOptions cuda_opts{};
    cuda_opts.device_id = 0;
    try {
        opts.AppendExecutionProvider_CUDA(cuda_opts);
        std::cout << "[YoloSeg] 使用 CUDA 推理\n";
    } catch (...) {
        std::cout << "[YoloSeg] CUDA 不可用，回退到 CPU\n";
    }

    session_  = Ort::Session(env_, model_path.c_str(), opts);
    mem_info_ = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    std::cout << "[YoloSeg] 模型加载完成: " << model_path << "\n";
}

// ─────────────────────────────────────────────────────────────────────────────
cv::Mat YoloSeg::preprocess(const cv::Mat& img_rgb,
                             float& scale, int& pad_x, int& pad_y)
{
    int h = img_rgb.rows, w = img_rgb.cols;
    int s = input_size_;
    scale = std::min((float)s / h, (float)s / w);
    int nh = (int)std::round(h * scale);
    int nw = (int)std::round(w * scale);
    pad_y  = (s - nh) / 2;
    pad_x  = (s - nw) / 2;

    cv::Mat resized;
    cv::resize(img_rgb, resized, {nw, nh}, 0, 0, cv::INTER_LINEAR);

    // letterbox canvas 填充 114
    cv::Mat canvas(s, s, CV_8UC3, cv::Scalar(114, 114, 114));
    resized.copyTo(canvas(cv::Rect(pad_x, pad_y, nw, nh)));

    // uint8 → float32，归一化到 [0,1]，HWC → CHW
    cv::Mat flt;
    canvas.convertTo(flt, CV_32FC3, 1.0 / 255.0);

    // 分离通道，拼成 [3, H, W] 连续内存
    std::vector<cv::Mat> chans(3);
    cv::split(flt, chans);
    cv::Mat blob;
    cv::vconcat(std::vector<cv::Mat>{chans[0].reshape(1,1),
                                     chans[1].reshape(1,1),
                                     chans[2].reshape(1,1)}, blob);
    return blob.reshape(1, {1, 3, s, s});   // 返回连续 float32 [1,3,s,s]
}

// ─────────────────────────────────────────────────────────────────────────────
std::vector<int> YoloSeg::nms(const std::vector<cv::Rect2f>& boxes,
                               const std::vector<float>& scores)
{
    std::vector<int> order(scores.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(),
              [&](int a, int b){ return scores[a] > scores[b]; });

    std::vector<bool> suppressed(scores.size(), false);
    std::vector<int>  keep;

    for (int i = 0; i < (int)order.size(); ++i) {
        int idx = order[i];
        if (suppressed[idx]) continue;
        keep.push_back(idx);
        float ax1 = boxes[idx].x, ay1 = boxes[idx].y;
        float ax2 = ax1 + boxes[idx].width;
        float ay2 = ay1 + boxes[idx].height;
        float aArea = boxes[idx].width * boxes[idx].height;

        for (int j = i + 1; j < (int)order.size(); ++j) {
            int jdx = order[j];
            if (suppressed[jdx]) continue;
            float bx1 = boxes[jdx].x, by1 = boxes[jdx].y;
            float bx2 = bx1 + boxes[jdx].width;
            float by2 = by1 + boxes[jdx].height;
            float inter_w = std::max(0.f, std::min(ax2,bx2) - std::max(ax1,bx1));
            float inter_h = std::max(0.f, std::min(ay2,by2) - std::max(ay1,by1));
            float inter   = inter_w * inter_h;
            float bArea   = boxes[jdx].width * boxes[jdx].height;
            float iou     = inter / (aArea + bArea - inter + 1e-6f);
            if (iou > iou_thresh_) suppressed[jdx] = true;
        }
    }
    return keep;
}

// ─────────────────────────────────────────────────────────────────────────────
std::vector<Detection> YoloSeg::postprocess(
    const float* out0, const float* out1,
    int orig_h, int orig_w,
    float scale, int pad_x, int pad_y)
{
    // out0: [1, 37, 8400]  → 转置为 [8400, 37]
    // out1: [1, 32, 160, 160]
    int s = input_size_;

    std::vector<cv::Rect2f> boxes;
    std::vector<float>      confs;
    std::vector<std::vector<float>> coeffs_list;

    for (int a = 0; a < NUM_ANCHORS; ++a) {
        // out0 是列主序 [37, 8400]，第 a 列
        float cx   = out0[0 * NUM_ANCHORS + a];
        float cy   = out0[1 * NUM_ANCHORS + a];
        float bw   = out0[2 * NUM_ANCHORS + a];
        float bh   = out0[3 * NUM_ANCHORS + a];
        float conf = out0[4 * NUM_ANCHORS + a];

        if (conf < conf_thresh_) continue;

        float x1 = cx - bw / 2.f;
        float y1 = cy - bh / 2.f;
        boxes.push_back({x1, y1, bw, bh});
        confs.push_back(conf);

        std::vector<float> c(NUM_PROTO_CH);
        for (int k = 0; k < NUM_PROTO_CH; ++k)
            c[k] = out0[(5 + k) * NUM_ANCHORS + a];
        coeffs_list.push_back(std::move(c));
    }

    if (boxes.empty()) return {};

    auto keep = nms(boxes, confs);
    if (keep.empty()) return {};

    std::vector<Detection> results;
    for (int idx : keep) {
        // 还原到原图坐标
        float x1 = (boxes[idx].x - pad_x) / scale;
        float y1 = (boxes[idx].y - pad_y) / scale;
        float x2 = (boxes[idx].x + boxes[idx].width  - pad_x) / scale;
        float y2 = (boxes[idx].y + boxes[idx].height - pad_y) / scale;
        x1 = std::max(0.f, std::min(x1, (float)orig_w));
        y1 = std::max(0.f, std::min(y1, (float)orig_h));
        x2 = std::max(0.f, std::min(x2, (float)orig_w));
        y2 = std::max(0.f, std::min(y2, (float)orig_h));

        // mask: coeffs @ proto → [160,160]
        // proto: [32, 160*160]
        cv::Mat mask_160(PROTO_HW, PROTO_HW, CV_32FC1, cv::Scalar(0));
        float* m = mask_160.ptr<float>();
        for (int hw = 0; hw < PROTO_HW * PROTO_HW; ++hw) {
            float val = 0.f;
            for (int k = 0; k < NUM_PROTO_CH; ++k)
                val += coeffs_list[idx][k] * out1[k * PROTO_HW * PROTO_HW + hw];
            // sigmoid
            m[hw] = 1.f / (1.f + std::exp(-val));
        }

        // resize 160×160 → input_size×input_size → 去 padding → 原图尺寸
        cv::Mat mask_full;
        cv::resize(mask_160, mask_full, {s, s}, 0, 0, cv::INTER_LINEAR);

        int crop_h = (int)std::round(orig_h * scale);
        int crop_w = (int)std::round(orig_w * scale);
        crop_h = std::min(crop_h, s - pad_y);
        crop_w = std::min(crop_w, s - pad_x);
        cv::Mat mask_crop = mask_full(cv::Rect(pad_x, pad_y, crop_w, crop_h));

        cv::Mat mask_orig;
        cv::resize(mask_crop, mask_orig, {orig_w, orig_h}, 0, 0, cv::INTER_LINEAR);

        cv::Mat mask_bin;
        cv::threshold(mask_orig, mask_bin, 0.5, 255, cv::THRESH_BINARY);
        mask_bin.convertTo(mask_bin, CV_8UC1);

        Detection det;
        det.bbox = cv::Rect((int)x1, (int)y1,
                            (int)(x2 - x1), (int)(y2 - y1));
        det.conf = confs[idx];
        det.mask = mask_bin;
        results.push_back(std::move(det));
    }
    return results;
}

// ─────────────────────────────────────────────────────────────────────────────
std::vector<Detection> YoloSeg::infer(const cv::Mat& img_rgb)
{
    float scale; int pad_x, pad_y;
    cv::Mat blob = preprocess(img_rgb, scale, pad_x, pad_y);

    // 确保连续
    cv::Mat blob_cont = blob.isContinuous() ? blob : blob.clone();

    int64_t s = input_size_;
    std::array<int64_t, 4> shape{1, 3, s, s};
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        mem_info_,
        blob_cont.ptr<float>(),
        blob_cont.total(),
        shape.data(), shape.size());

    const char* input_names[]  = {"images"};
    const char* output_names[] = {"output0", "output1"};

    auto outputs = session_.Run(
        Ort::RunOptions{nullptr},
        input_names,  &input_tensor, 1,
        output_names, 2);

    const float* out0 = outputs[0].GetTensorData<float>();
    const float* out1 = outputs[1].GetTensorData<float>();

    return postprocess(out0, out1,
                       img_rgb.rows, img_rgb.cols,
                       scale, pad_x, pad_y);
}
