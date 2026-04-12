cmake_minimum_required(VERSION 3.18)
project(pose_once C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# ── 依赖路径 ──────────────────────────────────────────────────────────────────
set(ORT_DIR "/home/ckh/Downloads/YOLOs-CPP/onnxruntime-linux-x64-gpu-1.16.3") # onnxruntime安装目录
set(CONDA_ENV "/home/ckh/anaconda3/envs/foundationpose") # conda环境根目录
set(PYTHON_VER "3.9") # python版本号

# ── ROS 2 ─────────────────────────────────────────────────────────────────────
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ── OpenCV ────────────────────────────────────────────────────────────────────
find_package(OpenCV REQUIRED) # 查找opencv库

# ── RealSense ─────────────────────────────────────────────────────────────────
find_package(realsense2 REQUIRED) # 查找intel realsense2 SDK

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
add_executable(pose_once_node
    src/main.cpp
    src/yolo_seg.cpp
    src/realsense_cam.cpp
    src/pose_utils.cpp
)

add_executable(client_example
    src/client_example.cpp
)

target_include_directories(pose_once_node PRIVATE
    include
    ${OpenCV_INCLUDE_DIRS}
    ${ORT_INCLUDE}
    ${PYTHON_INCLUDE}
    ${NUMPY_INCLUDE}
)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(pose_once_node PRIVATE
    ${OpenCV_LIBS}
    rclcpp::rclcpp
    realsense2
    ${ORT_LIB}
    ${PYTHON_LIB}
    ${cpp_typesupport_target}
)

target_link_libraries(client_example PRIVATE
    rclcpp::rclcpp
    ${cpp_typesupport_target}
)

# ONNX Runtime 的 CUDA provider 运行时需要能找到 so
# RPATH 只加 ORT 和 Python，不加整个 conda lib 目录
set_target_properties(pose_once_node PROPERTIES
    BUILD_RPATH "${ORT_DIR}/lib:${CONDA_ENV}/lib"
    INSTALL_RPATH "${ORT_DIR}/lib:${CONDA_ENV}/lib"
    BUILD_RPATH_USE_ORIGIN ON
)

# 链接时优先使用系统 libstdc++ / libgcc_s，避免 conda 版本污染 ROS 2
target_link_options(pose_once_node PRIVATE
    -Wl,-rpath-link,/usr/lib/x86_64-linux-gnu
    -Wl,--dynamic-linker=/lib64/ld-linux-x86-64.so.2
)

# ── 安装 ──────────────────────────────────────────────────────────────────────
install(TARGETS pose_once_node client_example
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()

message(STATUS "OpenCV: ${OpenCV_VERSION}")
message(STATUS "ORT:    ${ORT_DIR}")
message(STATUS "Python: ${PYTHON_INCLUDE}")
message(STATUS "NumPy:  ${NUMPY_INCLUDE}")
