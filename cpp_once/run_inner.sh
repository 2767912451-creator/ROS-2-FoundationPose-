#!/bin/bash --norc --noprofile
source /opt/ros/humble/setup.bash
source /home/ckh/vscode/FoundationPose/cpp_once/install/setup.bash

export LD_LIBRARY_PATH=\
/usr/local/cuda-11.8/lib64:\
/usr/local/cuda-11.8/targets/x86_64-linux/lib:\
/home/ckh/Downloads/YOLOs-CPP/onnxruntime-linux-x64-gpu-1.16.3/lib:\
/home/ckh/anaconda3/envs/foundationpose/lib/python3.9/site-packages/torch/lib:\
/home/ckh/vscode/FoundationPose/cpp_once/install/pose_once/lib:\
/opt/ros/humble/lib:\
/usr/local/lib:\
/usr/lib/x86_64-linux-gnu:\
/usr/lib

exec /home/ckh/vscode/FoundationPose/cpp_once/install/pose_once/lib/pose_once/pose_once_node "$@"
