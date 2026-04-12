# ROS 2 FoundationPose 位姿估计服务节点

## 概述

这是一个ROS 2服务节点，实现了"资源预加载 + 事件触发"的模式：
- **启动时**：加载模型（~10秒）
- **等待触发**：节点就绪，等待服务调用
- **触发时**：立即采集帧、检测、计算位姿（~3秒）

## 编译

确保你的ROS 2环境已配置，然后：

```bash
cd /path/to/workspace
colcon build --packages-select pose_once
source install/setup.bash
```

## 运行

### 1. 启动服务节点

```bash
ros2 run pose_once pose_once \
  --ros-args \
  -p mesh_file:=/path/to/your/mesh.obj \
  -p onnx_file:=/path/to/your/best.onnx \
  -p results_dir:=./results \
  -p debug_dir:=./debug \
  -p est_refine_iter:=3 \
  -p width:=640 \
  -p height:=480 \
  -p fps:=30
```

**参数说明：**
- `mesh_file`: 物体的3D模型文件路径
- `onnx_file`: YOLO分割模型路径
- `results_dir`: 结果图保存目录
- `debug_dir`: FoundationPose调试输出目录
- `est_refine_iter`: 位姿精化迭代次数
- `width/height/fps`: 相机分辨率和帧率

### 2. 触发服务

#### 方式A：命令行触发（测试用）

```bash
ros2 service call /trigger_pose_estimation pose_once/srv/TriggerPoseEstimation "{}"
```

#### 方式B：运行客户端示例

```bash
ros2 run pose_once client_example
```

#### 方式C：从C++代码调用

```cpp
#include <rclcpp/rclcpp.hpp>
#include "pose_once/srv/trigger_pose_estimation.hpp"

auto node = rclcpp::Node::make_shared("my_node");
auto client = node->create_client<pose_once::srv::TriggerPoseEstimation>(
    "trigger_pose_estimation");

auto request = std::make_shared<pose_once::srv::TriggerPoseEstimation::Request>();
auto result = client->async_send_request(request);

// 等待结果
if (rclcpp::spin_until_future_complete(node, result) == 
    rclcpp::FutureReturnCode::SUCCESS) {
    auto response = result.get();
    if (response->success) {
        // 处理位姿矩阵 response->pose (float64[16])
        // 这是一个4x4矩阵，行主序存储
    }
}
```

#### 方式D：从Python代码调用

```python
import rclpy
from pose_once.srv import TriggerPoseEstimation

rclpy.init()
node = rclpy.create_node('my_node')
client = node.create_client(TriggerPoseEstimation, 'trigger_pose_estimation')

while not client.wait_for_service(timeout_sec=1.0):
    print('等待服务...')

request = TriggerPoseEstimation.Request()
future = client.call_async(request)
rclpy.spin_until_future_complete(node, future)

response = future.result()
if response.success:
    print("位姿估计成功")
    pose_matrix = response.pose  # 4x4矩阵
else:
    print(f"失败: {response.message}")

rclpy.shutdown()
```

## 服务接口

### 服务名称
`/trigger_pose_estimation`

### 请求 (Request)
无参数

### 响应 (Response)
```
float64[16] pose      # 4x4位姿矩阵（行主序）
bool success          # 是否成功
string message        # 状态信息
```

**位姿矩阵格式：**
```
pose[0:4]   = [R00, R01, R02, T0]
pose[4:8]   = [R10, R11, R12, T1]
pose[8:12]  = [R20, R21, R22, T2]
pose[12:16] = [0,   0,   0,   1]
```

其中R是3x3旋转矩阵，T是3x1平移向量。

## 比赛场景集成

### 场景：底盘/云台MCU触发

在你的决策节点中：

```cpp
// 当机器人就位后，触发视觉识别
if (robot_ready_signal_received()) {
    auto client = node->create_client<pose_once::srv::TriggerPoseEstimation>(
        "trigger_pose_estimation");
    
    auto request = std::make_shared<pose_once::srv::TriggerPoseEstimation::Request>();
    auto result = client->async_send_request(request);
    
    // 等待结果（通常<3秒）
    if (rclcpp::spin_until_future_complete(node, result) == 
        rclcpp::FutureReturnCode::SUCCESS) {
        auto response = result.get();
        if (response->success) {
            // 发布位姿到其他节点
            publish_pose(response->pose);
        }
    }
}
```

## 日志输出

节点启动时会输出：
```
[INFO] ========== 初始化视觉节点 ==========
[INFO] 初始化 Python 环境...
[INFO] 加载 FoundationPose 模型...
[INFO] 初始化 YOLO 模型...
[INFO] 启动 RealSense 相机...
[INFO] GPU warmup...
[INFO] 初始化完成，耗时: 10.23 秒
[INFO] ========== 视觉节点就绪，等待触发 ==========
```

触发时会输出：
```
[INFO] 收到触发信号，开始位姿估计...
[INFO] 检测到物体，置信度=0.95，开始 register...
[INFO] 位姿估计完成，耗时: 2.87 秒
[INFO] 结果图已保存: ./results/pose_0001.jpg
```

## 故障排除

### 问题：找不到Python模块
**解决：** 确保你的conda环境已激活，且项目根目录在Python路径中

### 问题：相机无法打开
**解决：** 检查RealSense相机连接，运行 `rs-enumerate-devices` 验证

### 问题：YOLO推理失败
**解决：** 检查ONNX文件路径和CUDA环境

### 问题：FoundationPose初始化失败
**解决：** 检查mesh文件路径，确保模型文件存在且格式正确

## 性能指标

| 阶段 | 耗时 |
|------|------|
| 程序启动→模型加载完成 | ~10秒 |
| 等待触发 | 0秒（已就绪） |
| 触发→采集帧 | ~0.1秒 |
| YOLO检测 | ~0.5秒 |
| FoundationPose register | ~2.3秒 |
| **总响应时间** | **~3秒** ✅ |

## 下一步

- 集成到你的决策系统
- 添加位姿发布器（发布到其他ROS 2节点）
- 考虑添加多物体检测支持
- 优化YOLO和FoundationPose的参数以提升精度
