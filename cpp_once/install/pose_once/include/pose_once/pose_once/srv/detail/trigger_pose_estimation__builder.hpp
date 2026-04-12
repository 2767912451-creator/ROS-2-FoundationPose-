// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice

#ifndef POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__BUILDER_HPP_
#define POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "pose_once/srv/detail/trigger_pose_estimation__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace pose_once
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pose_once::srv::TriggerPoseEstimation_Request>()
{
  return ::pose_once::srv::TriggerPoseEstimation_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace pose_once


namespace pose_once
{

namespace srv
{

namespace builder
{

class Init_TriggerPoseEstimation_Response_message
{
public:
  explicit Init_TriggerPoseEstimation_Response_message(::pose_once::srv::TriggerPoseEstimation_Response & msg)
  : msg_(msg)
  {}
  ::pose_once::srv::TriggerPoseEstimation_Response message(::pose_once::srv::TriggerPoseEstimation_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::pose_once::srv::TriggerPoseEstimation_Response msg_;
};

class Init_TriggerPoseEstimation_Response_success
{
public:
  explicit Init_TriggerPoseEstimation_Response_success(::pose_once::srv::TriggerPoseEstimation_Response & msg)
  : msg_(msg)
  {}
  Init_TriggerPoseEstimation_Response_message success(::pose_once::srv::TriggerPoseEstimation_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_TriggerPoseEstimation_Response_message(msg_);
  }

private:
  ::pose_once::srv::TriggerPoseEstimation_Response msg_;
};

class Init_TriggerPoseEstimation_Response_pose
{
public:
  Init_TriggerPoseEstimation_Response_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TriggerPoseEstimation_Response_success pose(::pose_once::srv::TriggerPoseEstimation_Response::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_TriggerPoseEstimation_Response_success(msg_);
  }

private:
  ::pose_once::srv::TriggerPoseEstimation_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::pose_once::srv::TriggerPoseEstimation_Response>()
{
  return pose_once::srv::builder::Init_TriggerPoseEstimation_Response_pose();
}

}  // namespace pose_once

#endif  // POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__BUILDER_HPP_
