# pose_once - ROS 2 FoundationPose 位姿估计服务

一个基于 ROS 2 的实时 6D 位姿估计系统，集成 FoundationPose、YOLO 分割和 Intel RealSense 相机。

## 功能特性

- **实时 6D 位姿估计**：使用 FoundationPose 算法进行高精度位姿估计
- **自动物体检测**：集成 YOLO 分割模型进行物体检测和掩码生成
- **RealSense 集成**：支持 Intel RealSense 深度相机实时数据采集
- **ROS 2 服务接口**：通过 ROS 2 服务触发位姿估计，便于集成到机器人系统
- **GPU 加速**：支持 CUDA 加速的 ONNX Runtime 和 PyTorch
- **结果可视化**：自动保存位姿估计结果图像

## 系统要求

### 硬件
- NVIDIA GPU（支持 CUDA 11.8+）
- Intel RealSense 深度相机（D435/D455 等）
- 至少 8GB GPU 显存

### 软件
- Ubuntu 20.04 / 22.04
- ROS 2 Humble / Iron
- Python 3.9+
- CUDA 11.8+
- cuDNN 8.x

## 依赖安装

### 1. 系统依赖
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential cmake git \
    libopencv-dev python3-dev \
    librealsense2-dev librealsense2-utils
```

### 2. ROS 2 依赖
```bash
sudo apt-get install -y ros-humble-rclcpp ros-humble-rosidl-default-generators
```

### 3. Python 环境（Conda）
```bash
# 创建 conda 环境
conda create -n foundationpose python=3.9
conda activate foundationpose

# 安装 PyTorch（CUDA 11.8）
conda install pytorch::pytorch torchvision torchaudio pytorch-cuda=11.8 -c pytorch -c nvidia

# 安装其他依赖
pip install numpy opencv-python trimesh nvdiffrast onnxruntime-gpu
```

### 4. ONNX Runtime（GPU 版本）
```bash
# 下载 ONNX Runtime GPU 版本
wget https://github.com/microsoft/onnxruntime/releases/download/v1.16.3/onnxruntime-linux-x64-gpu-1.16.3.tgz
tar -xzf onnxruntime-linux-x64-gpu-1.16.3.tgz
# 记录解压路径，在 CMakeLists.txt 中配置
```

## 编译配置

### 修改 CMakeLists.txt

编辑 `CMakeLists.txt` 中的依赖路径：

```cmake
set(ORT_DIR "/path/to/onnxruntime-linux-x64-gpu-1.16.3")  # ONNX Runtime 路径
set(CONDA_ENV "/path/to/conda/envs/foundationpose")       # Conda 环境路径
set(PYTHON_VER "3.9")                                      # Python 版本
```

### 编译

```bash
# 在工作空间根目录
colcon build --packages-select pose_once --cmake-args -DCMAKE_BUILD_TYPE=Release

# 或使用 CMake 直接编译
cd cpp_once
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

## 项目结构

```
cpp_once/
├── CMakeLists.txt              # CMake 构建配置
├── package.xml                 # ROS 2 包配置
├── README.md                   # 本文件
├── include/
│   ├── pose_utils.hpp          # 位姿工具函数
│   ├── realsense_cam.hpp       # RealSense 相机接口
│   └── yolo_seg.hpp            # YOLO 分割模型接口
├── src/
│   ├── main.cpp                # ROS 2 节点主程序
│   ├── pose_utils.cpp          # 位姿工具实现
│   ├── realsense_cam.cpp       # 相机驱动实现
│   ├── yolo_seg.cpp            # YOLO 推理实现
│   └── client_example.cpp      # 服务客户端示例
├── srv/
│   └── TriggerPoseEstimation.srv  # ROS 2 服务定义
└── mycuda/                     # CUDA 自定义算子（可选）
```

## 使用方法

### 1. 启动位姿估计节点

```bash
# 激活 conda 环境
conda activate foundationpose

# 启动 ROS 2 节点
ros2 run pose_once pose_once \
    --ros-args \
    -p mesh_file:=/path/to/mesh.obj \
    -p onnx_file:=/path/to/best.onnx \
    -p results_dir:=./results \
    -p debug_dir:=./debug \
    -p est_refine_iter:=3 \
    -p width:=640 \
    -p height:=480 \
    -p fps:=30
```

### 2. 触发位姿估计

在另一个终端调用服务：

```bash
# 触发一次位姿估计
ros2 service call /trigger_pose_estimation pose_once/srv/TriggerPoseEstimation "{}"
```

### 3. 使用客户端示例

```bash
ros2 run pose_once client_example
```

## 参数说明

| 参数 | 类型 | 默认值 | 说明 |
|------|------|--------|------|
| `mesh_file` | string | `../demo_data/水杯.obj` | 物体 3D 模型文件路径 |
| `onnx_file` | string | `../weights/best.onnx` | YOLO 模型文件路径 |
| `results_dir` | string | `../results` | 结果保存目录 |
| `debug_dir` | string | `../debug` | 调试信息保存目录 |
| `est_refine_iter` | int | `3` | FoundationPose 迭代次数 |
| `width` | int | `640` | 相机图像宽度 |
| `height` | int | `480` | 相机图像高度 |
| `fps` | int | `30` | 相机帧率 |

## 服务接口

### TriggerPoseEstimation

**请求**：空请求

**响应**：
```
bool success          # 是否成功
string message        # 状态消息
float64[16] pose      # 4x4 位姿矩阵（行主序）
```

位姿矩阵格式（4x4 齐次变换矩阵）：
```
[R11 R12 R13 Tx]
[R21 R22 R23 Ty]
[R31 R32 R33 Tz]
[0   0   0   1 ]
```

其中 R 为旋转矩阵，(Tx, Ty, Tz) 为平移向量。

## 输出文件

### 结果目录 (results/)
- 位姿估计结果图像（带位姿文字标注）
- 文件名格式：`pose_YYYYMMDD_HHMMSS_mmm.jpg`

### 调试目录 (debug/)
- FoundationPose 中间结果
- 物体掩码、深度图等调试信息

## 工作流程

```
启动节点
  ↓
预加载模型（FoundationPose、YOLO）
  ↓
启动 RealSense 相机
  ↓
等待服务触发
  ↓
收到触发信号
  ↓
采集一帧（RGB + 深度）
  ↓
YOLO 分割检测物体
  ↓
FoundationPose register 估计位姿
  ↓
返回位姿结果 + 保存可视化图像
```

## 常见问题

### Q: 编译时找不到 ONNX Runtime
**A**: 检查 CMakeLists.txt 中的 `ORT_DIR` 路径是否正确，确保包含 `include/` 和 `lib/` 目录。

### Q: 运行时 Python 模块导入失败
**A**: 确保 conda 环境已激活，且 `estimater` 模块在 Python 路径中。检查 `sys.path` 配置。

### Q: 相机无法连接
**A**: 运行 `realsense-viewer` 检查相机是否被识别，确保 librealsense2 已正确安装。

### Q: GPU 显存不足
**A**: 减少 `est_refine_iter` 参数或降低图像分辨率。

### Q: 位姿估计精度不高
**A**: 
- 检查 YOLO 模型的检测质量
- 增加 `est_refine_iter` 迭代次数
- 确保相机标定参数正确

## 性能指标

| 模块 | 耗时 |
|------|------|
| YOLO 检测 | ~50-100ms |
| FoundationPose register | ~200-500ms（取决于迭代次数） |
| 总耗时 | ~300-700ms |

## 许可证

Apache License 2.0

## 作者

王兰花 <2767912451@qq.com>

## 参考文献

- [FoundationPose](https://github.com/NVlabs/FoundationPose)
- [ROS 2 Documentation](https://docs.ros.org/en/humble/)
- [Intel RealSense SDK](https://github.com/IntelRealSense/librealsense)
- [YOLO Segmentation](https://github.com/ultralytics/ultralytics)

## 更新日志

### v0.0.1 (2024-XX-XX)
- 初始版本
- 支持 ROS 2 服务接口
- 集成 FoundationPose、YOLO、RealSense
