# pose_once - ROS 2 FoundationPose 位姿估计节点

基于 ROS 2 的 6D 位姿估计系统，集成 FoundationPose、YOLO 实例分割和 Intel RealSense 相机。

## 系统要求

- NVIDIA GPU（CUDA 11.8+，建议 8GB 显存）
- Intel RealSense 深度相机
- Ubuntu 22.04 + ROS 2 Humble
- Conda 环境 `foundationpose`（Python 3.9）
- ONNX Runtime GPU 1.16.3

## 编译前配置

修改 `CMakeLists.txt` 中的路径：

```cmake
set(ORT_DIR "/home/ckh/Downloads/YOLOs-CPP/onnxruntime-linux-x64-gpu-1.16.3")
set(CONDA_ENV "/home/ckh/anaconda3/envs/foundationpose")
set(PYTHON_VER "3.9")
```

## 编译

```bash
cd cpp_once
source /opt/ros/humble/setup.bash
colcon build --packages-select pose_once
```

## 使用

```bash
# 终端 1：启动节点（foundationpose conda 环境）
./run.sh --ros-args -p mesh_file:=/home/ckh/vscode/FoundationPose/demo_data/水杯.obj

# 终端 2：触发一次位姿估计
./trigger.sh
```

## 参数

| 参数 | 默认值 | 说明 |
|------|--------|------|
| `mesh_file` | `../demo_data/水杯.obj` | 物体 CAD 模型路径（.obj） |
| `onnx_file` | `models/best.onnx` | YOLO 分割模型路径 |
| `results_dir` | `results` | 可视化结果图保存目录 |
| `debug_dir` | `../debug` | FoundationPose 调试输出目录 |
| `est_refine_iter` | `3` | FoundationPose 精化迭代次数 |
| `width` | `640` | 相机采集宽度（像素） |
| `height` | `480` | 相机采集高度（像素） |
| `fps` | `30` | 相机帧率 |
| `camera_frame` | `camera_color_optical_frame` | 相机坐标系名称 |
| `target_frame` | `base_link` | 位姿输出目标坐标系 |

## 服务接口

**服务名**：`/trigger_pose_estimation`  
**类型**：`pose_once/srv/TriggerPoseEstimation`

```
# 请求（空）
---
# 响应
bool success
string message
float64[16] pose    # 4x4 位姿矩阵，行主序
```

## 发布话题

**话题名**：`/detect/grasp_pose`  
**类型**：`geometry_msgs/PoseStamped`  
**坐标系**：`target_frame`（默认 `base_link`）

## 工作流程

```
启动节点 → 预加载模型（~12秒）→ 等待触发
    ↓ 收到 /trigger_pose_estimation 请求
采集 RGB-D 帧 → YOLO 实例分割 → FoundationPose 位姿估计
    ↓
发布 /detect/grasp_pose + 保存可视化结果图至 results/
```

## 注意事项

- `run.sh` 使用干净的系统环境启动节点，避免 conda `libstdc++` 版本污染 ROS 2
- RPATH 已配置为优先加载 ORT 和 conda Python 库，无需手动设置 `LD_LIBRARY_PATH`
- 编译产物位于 `install/pose_once/lib/pose_once/pose_once_node`
