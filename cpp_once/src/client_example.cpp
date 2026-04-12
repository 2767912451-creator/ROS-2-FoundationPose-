// ==============================================================================
// 客户端示例：触发位姿估计服务
// 编译：colcon build --packages-select pose_once
// 运行：ros2 run pose_once client_example
// ==============================================================================

#include <rclcpp/rclcpp.hpp>
#include "pose_once/srv/trigger_pose_estimation.hpp"
#include <iostream>
#include <iomanip>

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("pose_client");

    auto client = node->create_client<pose_once::srv::TriggerPoseEstimation>(
        "trigger_pose_estimation");

    // 等待服务就绪
    while (!client->wait_for_service(std::chrono::seconds(1))) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(node->get_logger(), "Interrupted while waiting for service");
            return 1;
        }
        RCLCPP_INFO(node->get_logger(), "等待服务就绪...");
    }

    auto request = std::make_shared<pose_once::srv::TriggerPoseEstimation::Request>();

    RCLCPP_INFO(node->get_logger(), "发送触发信号...");
    auto result = client->async_send_request(request);

    // 等待结果
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS) {
        auto response = result.get();
        RCLCPP_INFO(node->get_logger(), "服务调用成功");
        RCLCPP_INFO(node->get_logger(), "Success: %s", response->success ? "true" : "false");
        RCLCPP_INFO(node->get_logger(), "Message: %s", response->message.c_str());

        if (response->success) {
            RCLCPP_INFO(node->get_logger(), "位姿矩阵 (4x4):");
            for (int i = 0; i < 4; ++i) {
                std::cout << "  ";
                for (int j = 0; j < 4; ++j) {
                    std::cout << std::fixed << std::setprecision(4)
                              << response->pose[i * 4 + j] << " ";
                }
                std::cout << "\n";
            }
        }
    } else {
        RCLCPP_ERROR(node->get_logger(), "服务调用失败");
        return 1;
    }

    rclcpp::shutdown();
    return 0;
}
