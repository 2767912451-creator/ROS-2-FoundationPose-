// ==============================================================================
// ROS 2 版本：FoundationPose 位姿估计服务节点
// 流程：启动时预加载模型 → 等待服务触发 → 收到触发后采集帧 → YOLO检测 → 
//       FoundationPose register → 返回位姿
//
// 编译：colcon build --packages-select pose_once
// 运行：ros2 run pose_once pose_once --ros-args -p mesh_file:=/path/to/mesh.obj -p onnx_file:=/path/to/cpp_once/models/best.onnx
// 触发：ros2 service call /trigger_pose_estimation pose_once/srv/TriggerPoseEstimation "{}"
// ==============================================================================

#include "yolo_seg.hpp"
#include "realsense_cam.hpp"
#include "pose_utils.hpp"

#include <rclcpp/rclcpp.hpp>
#include "pose_once/srv/trigger_pose_estimation.hpp"

#include <Python.h>
#include <numpy/arrayobject.h>

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

// ── Python 嵌入：调用 FoundationPose register ─────────────────────────────────
static cv::Mat callFoundationPoseRegister(
    PyObject* py_est,
    const cv::Mat& color_rgb,
    const cv::Mat& depth_f32,
    const cv::Mat& mask_u8,
    const cv::Mat& K,
    int iteration)
{
    npy_intp dims_c[3] = {color_rgb.rows, color_rgb.cols, 3};
    PyObject* np_color = PyArray_SimpleNewFromData(
        3, dims_c, NPY_UINT8, (void*)color_rgb.data);

    npy_intp dims_d[2] = {depth_f32.rows, depth_f32.cols};
    PyObject* np_depth = PyArray_SimpleNewFromData(
        2, dims_d, NPY_FLOAT, (void*)depth_f32.data);

    cv::Mat mask_bool;
    mask_u8.convertTo(mask_bool, CV_8UC1);
    int nonzero = cv::countNonZero(mask_bool);
    PyObject* np_mask = PyArray_SimpleNewFromData(
        2, dims_d, NPY_BOOL, (void*)mask_bool.data);

    npy_intp dims_k[2] = {3, 3};
    PyObject* np_K = PyArray_SimpleNewFromData(
        2, dims_k, NPY_DOUBLE, (void*)K.data);

    PyObject* kwargs = PyDict_New();
    PyDict_SetItemString(kwargs, "K",        np_K);
    PyDict_SetItemString(kwargs, "rgb",      np_color);
    PyDict_SetItemString(kwargs, "depth",    np_depth);
    PyDict_SetItemString(kwargs, "ob_mask",  np_mask);
    PyDict_SetItemString(kwargs, "iteration", PyLong_FromLong(iteration));

    PyObject* method = PyObject_GetAttrString(py_est, "register");
    PyObject* result = PyObject_Call(method, PyTuple_New(0), kwargs);

    Py_DECREF(method);
    Py_DECREF(kwargs);
    Py_DECREF(np_color);
    Py_DECREF(np_depth);
    Py_DECREF(np_mask);
    Py_DECREF(np_K);

    if (!result) {
        PyErr_Print();
        return {};
    }

    PyObject* contiguous = PyArray_FROM_OTF(result, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);
    Py_DECREF(result);
    if (!contiguous) { PyErr_Print(); return {}; }

    double* src = (double*)PyArray_DATA((PyArrayObject*)contiguous);
    cv::Mat pose(4, 4, CV_64F);
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            pose.at<double>(r, c) = src[r * 4 + c];

    Py_DECREF(contiguous);
    return pose;
}

// ── ROS 2 节点类 ──────────────────────────────────────────────────────────────
class PoseEstimationNode : public rclcpp::Node {
private:
    // 预加载的资源
    std::unique_ptr<YoloSeg> yolo_;
    std::unique_ptr<RealSenseCam> cam_;
    PyObject* py_est_;
    cv::Mat K_;
    float depth_scale_;
    int est_refine_iter_;
    std::string results_dir_;
    std::string debug_dir_;

    // 服务端
    rclcpp::Service<pose_once::srv::TriggerPoseEstimation>::SharedPtr service_;

public:
    PoseEstimationNode() : Node("pose_estimation_node"), py_est_(nullptr) {
        // 声明参数
        this->declare_parameter("mesh_file", "../demo_data/水杯.obj");
        this->declare_parameter("onnx_file", "models/best.onnx");
        this->declare_parameter("results_dir", "results");
        this->declare_parameter("debug_dir", "../debug");
        this->declare_parameter("est_refine_iter", 3);
        this->declare_parameter("width", 640);
        this->declare_parameter("height", 480);
        this->declare_parameter("fps", 30);

        // 获取参数
        std::string mesh_file = this->get_parameter("mesh_file").as_string();
        std::string onnx_file = this->get_parameter("onnx_file").as_string();
        results_dir_ = this->get_parameter("results_dir").as_string();
        debug_dir_ = this->get_parameter("debug_dir").as_string();
        est_refine_iter_ = this->get_parameter("est_refine_iter").as_int();
        int width = this->get_parameter("width").as_int();
        int height = this->get_parameter("height").as_int();
        int fps = this->get_parameter("fps").as_int();

        fs::create_directories(results_dir_);
        fs::create_directories(debug_dir_);

        RCLCPP_INFO(this->get_logger(), "========== 初始化视觉节点 ==========");
        auto t_init_start = std::chrono::steady_clock::now();

        // ── 初始化 Python ──────────────────────────────────────────────────────
        RCLCPP_INFO(this->get_logger(), "初始化 Python 环境...");
        Py_Initialize();
        import_array();

        std::string proj_root = fs::absolute("..").string();
        PyRun_SimpleString(("import sys; sys.path.insert(0, '" + proj_root + "')").c_str());

        PyObject* py_module = PyImport_ImportModule("estimater");
        if (!py_module) {
            PyErr_Print();
            throw std::runtime_error("Failed to import estimater module");
        }

        // ── 初始化 FoundationPose ──────────────────────────────────────────────
        RCLCPP_INFO(this->get_logger(), "加载 FoundationPose 模型...");
        std::string init_script = R"(
import trimesh, numpy as np, nvdiffrast.torch as dr
from estimater import *

mesh = trimesh.load(')" + mesh_file + R"(')
if isinstance(mesh, trimesh.Scene):
    mesh = trimesh.util.concatenate(list(mesh.geometry.values()))
mesh.vertices /= 1000.0

scorer  = ScorePredictor()
refiner = PoseRefinePredictor()
glctx   = dr.RasterizeCudaContext()
est = FoundationPose(
    model_pts=mesh.vertices,
    model_normals=mesh.vertex_normals,
    mesh=mesh,
    scorer=scorer, refiner=refiner,
    debug_dir=')" + debug_dir_ + R"(',
    debug=1, glctx=glctx)
print('[Python] FoundationPose 初始化完成')
)";

        if (PyRun_SimpleString(init_script.c_str()) != 0) {
            PyErr_Print();
            throw std::runtime_error("Failed to initialize FoundationPose");
        }

        PyObject* main_mod = PyImport_AddModule("__main__");
        py_est_ = PyObject_GetAttrString(main_mod, "est");
        if (!py_est_) {
            PyErr_Print();
            throw std::runtime_error("Failed to get est object");
        }

        Py_DECREF(py_module);

        // ── 初始化 YOLO ────────────────────────────────────────────────────────
        RCLCPP_INFO(this->get_logger(), "初始化 YOLO 模型...");
        yolo_ = std::make_unique<YoloSeg>(onnx_file, 0.25f, 0.45f, 640);

        // ── 启动相机 ───────────────────────────────────────────────────────────
        RCLCPP_INFO(this->get_logger(), "启动 RealSense 相机...");
        cam_ = std::make_unique<RealSenseCam>(width, height, fps);
        K_ = cam_->getK();
        depth_scale_ = cam_->getDepthScale();

        // ── GPU warmup ─────────────────────────────────────────────────────────
        RCLCPP_INFO(this->get_logger(), "GPU warmup...");
        cv::Mat dummy(height, width, CV_8UC3, cv::Scalar(0));
        yolo_->infer(dummy);

        auto t_init_end = std::chrono::steady_clock::now();
        double init_time = std::chrono::duration<double>(t_init_end - t_init_start).count();
        RCLCPP_INFO(this->get_logger(), "初始化完成，耗时: %.2f 秒", init_time);

        // ── 创建服务 ───────────────────────────────────────────────────────────
        service_ = this->create_service<pose_once::srv::TriggerPoseEstimation>(
            "trigger_pose_estimation",
            std::bind(&PoseEstimationNode::handle_trigger, this,
                      std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "========== 视觉节点就绪，等待触发 ==========");
    }

    ~PoseEstimationNode() {
        if (py_est_) Py_DECREF(py_est_);
        Py_Finalize();
    }

private:
    void handle_trigger(
        const std::shared_ptr<pose_once::srv::TriggerPoseEstimation::Request> request,
        std::shared_ptr<pose_once::srv::TriggerPoseEstimation::Response> response) {

        RCLCPP_INFO(this->get_logger(), "收到触发信号，开始位姿估计...");
        auto t_start = std::chrono::steady_clock::now();

        try {
            // 获取一帧
            FramePair fp = cam_->waitForFrame();

            // YOLO 检测
            auto dets = yolo_->infer(fp.color_rgb);

            if (dets.empty()) {
                RCLCPP_WARN(this->get_logger(), "未检测到物体");
                response->success = false;
                response->message = "未检测到物体";
                return;
            }

            // 置信度最高的检测
            auto& best = *std::max_element(dets.begin(), dets.end(),
                [](const Detection& a, const Detection& b){ return a.conf < b.conf; });

            RCLCPP_INFO(this->get_logger(), "检测到物体，置信度=%.2f，开始 register...", best.conf);

            // 深度转换
            cv::Mat depth_f32;
            fp.depth_raw.convertTo(depth_f32, CV_32FC1, depth_scale_);

            // FoundationPose register
            cv::Mat pose = callFoundationPoseRegister(
                py_est_, fp.color_rgb, depth_f32, best.mask, K_, est_refine_iter_);

            if (pose.empty()) {
                RCLCPP_ERROR(this->get_logger(), "位姿估计失败");
                response->success = false;
                response->message = "位姿估计失败";
                return;
            }

            // 转换为服务响应格式
            memcpy(response->pose.data(), pose.ptr<double>(), 16 * sizeof(double));
            response->success = true;
            response->message = "位姿估计成功";

            // 保存结果
            cv::Mat vis_bgr;
            cv::cvtColor(fp.color_rgb, vis_bgr, cv::COLOR_RGB2BGR);
            cv::rectangle(vis_bgr, best.bbox, {0,255,0}, 2);
            drawPoseText(vis_bgr, pose);
            std::string save_path = savePoseImage(vis_bgr, results_dir_);

            auto t_end = std::chrono::steady_clock::now();
            double dt = std::chrono::duration<double>(t_end - t_start).count();
            RCLCPP_INFO(this->get_logger(), "位姿估计完成，耗时: %.2f 秒", dt);
            RCLCPP_INFO(this->get_logger(), "结果图已保存: %s", save_path.c_str());

            printPose(pose);

        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "异常: %s", e.what());
            response->success = false;
            response->message = std::string("异常: ") + e.what();
        }
    }
};

// ── Main ───────────────────────────────────────────────────────────────────────
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    try {
        auto node = std::make_shared<PoseEstimationNode>();
        rclcpp::spin(node);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    rclcpp::shutdown();
    return 0;
}
