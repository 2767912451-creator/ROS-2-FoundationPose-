# 工作空间文件说明

## 根目录

| 文件/文件夹 | 说明 |
|------------|------|
| `estimater.py` | FoundationPose 核心算法，包含 `FoundationPose`、`ScorePredictor`、`PoseRefinePredictor` 类 |
| `Utils.py` | 通用工具函数库，渲染、点云、坐标变换等，被 `estimater.py` 依赖 |
| `mycpp.cpython-39-x86_64-linux-gnu.so` | mycpp 编译产物，供 `estimater.py` 调用（`cluster_poses` 等函数） |
| `requirements.txt` | Python 依赖列表 |
| `.gitignore` | Git 忽略配置 |
| `WORKSPACE_GUIDE.md` | 本文件 |

---

## 文件夹

| 文件夹 | 说明 |
|--------|------|
| `cpp_once/` | ROS 2 集成节点，见下方详细说明 |
| `learning/` | 神经网络模型定义（scorer、refiner），`estimater.py` 运行时依赖 |
| `bundlesdf/` | 包含 `mycuda` CUDA 扩展，被 `Utils.py` 依赖，不可删除 |
| `mycpp/` | `mycpp.so` 的 C++ 源码和 CMake 构建文件 |
| `weights/` | FoundationPose 预训练模型权重，节点启动时加载，不可删除 |
| `demo_data/` | CAD 模型文件，包含 `水杯.obj` |
| `debug/` | 运行时调试输出，自动生成 |

---

## cpp_once/

ROS 2 节点，实现"触发一次 → 估计位姿 → 发布结果"的完整流程。

| 文件/文件夹 | 说明 |
|------------|------|
| `src/main.cpp` | 节点主程序，预加载模型，等待服务触发，调用 YOLO + FoundationPose，发布抓取位姿 |
| `src/yolo_seg.cpp` | YOLO 实例分割推理（ONNX Runtime + CUDA） |
| `src/realsense_cam.cpp` | Intel RealSense 相机驱动，采集对齐的 RGB + 深度帧 |
| `src/pose_utils.cpp` | 位姿可视化工具（绘制文字、坐标轴、保存结果图） |
| `src/client_example.cpp` | 触发服务的客户端，用于测试 |
| `include/` | 上述各模块的头文件 |
| `srv/TriggerPoseEstimation.srv` | ROS 2 服务定义，请求为空，响应包含 4x4 位姿矩阵 |
| `models/` | YOLO 模型文件（best.onnx、best.pt） |
| `results/` | 每次估计后保存的可视化结果图 |
| `CMakeLists.txt` | CMake 构建配置，需按实际路径修改 ORT_DIR、CONDA_ENV |
| `package.xml` | ROS 2 包依赖声明 |
| `run.sh` | 启动节点的脚本（用干净环境绕过 conda 库污染问题） |
| `trigger.sh` | 发送触发信号的快捷脚本 |
| `build/` | colcon 编译中间产物（自动生成） |
| `install/` | colcon 安装产物，节点二进制在 `install/pose_once/lib/pose_once/` |
| `log/` | colcon 编译日志（自动生成） |

---

## 使用流程

```bash
# 终端 1：编译并启动节点（foundationpose conda 环境）
cd cpp_once
source /opt/ros/humble/setup.bash
colcon build --packages-select pose_once
./run.sh --ros-args -p mesh_file:=/home/ckh/vscode/FoundationPose/demo_data/水杯.obj

# 终端 2：触发一次位姿估计（base 环境）
./trigger.sh
```

节点发布 `/detect/grasp_pose`（`geometry_msgs/PoseStamped`），包含杯子在 `base_link` 坐标系下的 6DOF 抓取位姿。
