#!/bin/sh
# 完全绕过 bash，用 env -i 直接运行节点二进制
# librealsense2 内部捆绑了 fastdds，需用 LD_PRELOAD 强制先加载 ROS 2 的版本
exec /usr/bin/env -i \
    HOME="$HOME" \
    USER="$USER" \
    LANG=zh_CN.UTF-8 \
    LC_ALL=zh_CN.UTF-8 \
    ROS_DISTRO=humble \
    ROS_VERSION=2 \
    ROS_PYTHON_VERSION=3 \
    AMENT_PREFIX_PATH=/home/ckh/vscode/FoundationPose/cpp_once/install/pose_once:/opt/ros/humble \
    COLCON_PREFIX_PATH=/home/ckh/vscode/FoundationPose/cpp_once/install \
    PATH="/opt/ros/humble/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin" \
    PYTHONPATH="/opt/ros/humble/lib/python3.10/site-packages:/opt/ros/humble/local/lib/python3.10/dist-packages" \
    LD_PRELOAD="/opt/ros/humble/lib/libfastrtps.so.2.6:/opt/ros/humble/lib/libfastcdr.so.1.0.24" \
    LD_LIBRARY_PATH="/usr/local/cuda-11.8/lib64:/usr/local/cuda-11.8/targets/x86_64-linux/lib:/home/ckh/Downloads/YOLOs-CPP/onnxruntime-linux-x64-gpu-1.16.3/lib:/home/ckh/anaconda3/envs/foundationpose/lib/python3.9/site-packages/torch/lib:/home/ckh/vscode/FoundationPose/cpp_once/install/pose_once/lib:/opt/ros/humble/lib:/usr/local/lib:/usr/lib/x86_64-linux-gnu:/usr/lib" \
    /home/ckh/vscode/FoundationPose/cpp_once/install/pose_once/lib/pose_once/pose_once_node "$@"
