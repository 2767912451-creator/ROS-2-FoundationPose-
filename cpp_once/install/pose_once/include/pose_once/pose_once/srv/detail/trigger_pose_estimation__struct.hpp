// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice

#ifndef POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_HPP_
#define POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__pose_once__srv__TriggerPoseEstimation_Request __attribute__((deprecated))
#else
# define DEPRECATED__pose_once__srv__TriggerPoseEstimation_Request __declspec(deprecated)
#endif

namespace pose_once
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TriggerPoseEstimation_Request_
{
  using Type = TriggerPoseEstimation_Request_<ContainerAllocator>;

  explicit TriggerPoseEstimation_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit TriggerPoseEstimation_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pose_once__srv__TriggerPoseEstimation_Request
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pose_once__srv__TriggerPoseEstimation_Request
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TriggerPoseEstimation_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const TriggerPoseEstimation_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TriggerPoseEstimation_Request_

// alias to use template instance with default allocator
using TriggerPoseEstimation_Request =
  pose_once::srv::TriggerPoseEstimation_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pose_once


#ifndef _WIN32
# define DEPRECATED__pose_once__srv__TriggerPoseEstimation_Response __attribute__((deprecated))
#else
# define DEPRECATED__pose_once__srv__TriggerPoseEstimation_Response __declspec(deprecated)
#endif

namespace pose_once
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct TriggerPoseEstimation_Response_
{
  using Type = TriggerPoseEstimation_Response_<ContainerAllocator>;

  explicit TriggerPoseEstimation_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 16>::iterator, double>(this->pose.begin(), this->pose.end(), 0.0);
      this->success = false;
      this->message = "";
    }
  }

  explicit TriggerPoseEstimation_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pose(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<double, 16>::iterator, double>(this->pose.begin(), this->pose.end(), 0.0);
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _pose_type =
    std::array<double, 16>;
  _pose_type pose;
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__pose(
    const std::array<double, 16> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__pose_once__srv__TriggerPoseEstimation_Response
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__pose_once__srv__TriggerPoseEstimation_Response
    std::shared_ptr<pose_once::srv::TriggerPoseEstimation_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TriggerPoseEstimation_Response_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const TriggerPoseEstimation_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TriggerPoseEstimation_Response_

// alias to use template instance with default allocator
using TriggerPoseEstimation_Response =
  pose_once::srv::TriggerPoseEstimation_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace pose_once

namespace pose_once
{

namespace srv
{

struct TriggerPoseEstimation
{
  using Request = pose_once::srv::TriggerPoseEstimation_Request;
  using Response = pose_once::srv::TriggerPoseEstimation_Response;
};

}  // namespace srv

}  // namespace pose_once

#endif  // POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_HPP_
