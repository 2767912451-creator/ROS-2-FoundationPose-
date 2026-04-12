cmake_minimum_required(VERSION 3.18)
project(pose_once CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# ── 依赖路径 ──────────────────────────────────────────────────────────────────
set(ORT_DIR "/home/ckh/Downloads/YOLOs-CPP/onnxruntime-linux-x64-gpu-1.16.3")//onnxruntime安装目录
set(CONDA_ENV "/home/ckh/anaconda3/envs/foundationpose")//canda环境根目录
set(PYTHON_VER "3.9")//python版本号

# ── ROS 2 ─────────────────────────────────────────────────────────────────────
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ── OpenCV ────────────────────────────────────────────────────────────────────
find_package(OpenCV REQUIRED)//查找opencv库

# ── RealSense ─────────────────────────────────────────────────────────────────
find_package(realsense2 REQUIRED)//查找intel realsense2 SDK

# ── ONNX Runtime ──────────────────────────────────────────────────────────────
set(ORT_INCLUDE "${ORT_DIR}/include")
set(ORT_LIB     "${ORT_DIR}/lib/libonnxruntime.so")

# ── Python + NumPy（conda 环境）───────────────────────────────────────────────
set(PYTHON_INCLUDE "${CONDA_ENV}/include/python${PYTHON_VER}")
set(PYTHON_LIB     "${CONDA_ENV}/lib/libpython${PYTHON_VER}.so")
set(NUMPY_INCLUDE  "${CONDA_ENV}/lib/python${PYTHON_VER}/site-packages/numpy/core/include")

# ── 生成服务接口 ──────────────────────────────────────────────────────────────
rosidl_generate_interfaces(${PROJECT_NAME}
    "srv/TriggerPoseEstimation.srv"
)

# ── 目标 ──────────────────────────────────────────────────────────────────────
add_executable(pose_once
    src/main.cpp
    src/yolo_seg.cpp
    src/realsense_cam.cpp
    src/pose_utils.cpp
)

add_executable(client_example
    src/client_example.cpp
)

target_include_directories(pose_once PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
    ${ORT_INCLUDE}
    ${PYTHON_INCLUDE}
    ${NUMPY_INCLUDE}
)

target_link_libraries(pose_once PRIVATE
    ${OpenCV_LIBS}
    rclcpp::rclcpp
    realsense2
    ${ORT_LIB}
    ${PYTHON_LIB}
)

target_link_libraries(client_example PRIVATE
    rclcpp::rclcpp
)

rosidl_target_interfaces(pose_once
    ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

rosidl_target_interfaces(client_example
    ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

# ONNX Runtime 的 CUDA provider 运行时需要能找到 so
set_target_properties(pose_once PROPERTIES
    BUILD_RPATH "${ORT_DIR}/lib"
    INSTALL_RPATH "${ORT_DIR}/lib"
)

ament_package()

message(STATUS "OpenCV: ${OpenCV_VERSION}")
message(STATUS "ORT:    ${ORT_DIR}")
message(STATUS "Python: ${PYTHON_INCLUDE}")
message(STATUS "NumPy:  ${NUMPY_INCLUDE}")
