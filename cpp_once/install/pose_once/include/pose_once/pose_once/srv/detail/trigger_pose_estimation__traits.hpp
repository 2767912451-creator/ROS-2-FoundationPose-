// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice

#ifndef POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__TRAITS_HPP_
#define POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "pose_once/srv/detail/trigger_pose_estimation__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace pose_once
{

namespace srv
{

inline void to_flow_style_yaml(
  const TriggerPoseEstimation_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TriggerPoseEstimation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TriggerPoseEstimation_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pose_once

namespace rosidl_generator_traits
{

[[deprecated("use pose_once::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pose_once::srv::TriggerPoseEstimation_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  pose_once::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pose_once::srv::to_yaml() instead")]]
inline std::string to_yaml(const pose_once::srv::TriggerPoseEstimation_Request & msg)
{
  return pose_once::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pose_once::srv::TriggerPoseEstimation_Request>()
{
  return "pose_once::srv::TriggerPoseEstimation_Request";
}

template<>
inline const char * name<pose_once::srv::TriggerPoseEstimation_Request>()
{
  return "pose_once/srv/TriggerPoseEstimation_Request";
}

template<>
struct has_fixed_size<pose_once::srv::TriggerPoseEstimation_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<pose_once::srv::TriggerPoseEstimation_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<pose_once::srv::TriggerPoseEstimation_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace pose_once
{

namespace srv
{

inline void to_flow_style_yaml(
  const TriggerPoseEstimation_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose
  {
    if (msg.pose.size() == 0) {
      out << "pose: []";
    } else {
      out << "pose: [";
      size_t pending_items = msg.pose.size();
      for (auto item : msg.pose) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TriggerPoseEstimation_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose.size() == 0) {
      out << "pose: []\n";
    } else {
      out << "pose:\n";
      for (auto item : msg.pose) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TriggerPoseEstimation_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace pose_once

namespace rosidl_generator_traits
{

[[deprecated("use pose_once::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const pose_once::srv::TriggerPoseEstimation_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  pose_once::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use pose_once::srv::to_yaml() instead")]]
inline std::string to_yaml(const pose_once::srv::TriggerPoseEstimation_Response & msg)
{
  return pose_once::srv::to_yaml(msg);
}

template<>
inline const char * data_type<pose_once::srv::TriggerPoseEstimation_Response>()
{
  return "pose_once::srv::TriggerPoseEstimation_Response";
}

template<>
inline const char * name<pose_once::srv::TriggerPoseEstimation_Response>()
{
  return "pose_once/srv/TriggerPoseEstimation_Response";
}

template<>
struct has_fixed_size<pose_once::srv::TriggerPoseEstimation_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<pose_once::srv::TriggerPoseEstimation_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<pose_once::srv::TriggerPoseEstimation_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<pose_once::srv::TriggerPoseEstimation>()
{
  return "pose_once::srv::TriggerPoseEstimation";
}

template<>
inline const char * name<pose_once::srv::TriggerPoseEstimation>()
{
  return "pose_once/srv/TriggerPoseEstimation";
}

template<>
struct has_fixed_size<pose_once::srv::TriggerPoseEstimation>
  : std::integral_constant<
    bool,
    has_fixed_size<pose_once::srv::TriggerPoseEstimation_Request>::value &&
    has_fixed_size<pose_once::srv::TriggerPoseEstimation_Response>::value
  >
{
};

template<>
struct has_bounded_size<pose_once::srv::TriggerPoseEstimation>
  : std::integral_constant<
    bool,
    has_bounded_size<pose_once::srv::TriggerPoseEstimation_Request>::value &&
    has_bounded_size<pose_once::srv::TriggerPoseEstimation_Response>::value
  >
{
};

template<>
struct is_service<pose_once::srv::TriggerPoseEstimation>
  : std::true_type
{
};

template<>
struct is_service_request<pose_once::srv::TriggerPoseEstimation_Request>
  : std::true_type
{
};

template<>
struct is_service_response<pose_once::srv::TriggerPoseEstimation_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__TRAITS_HPP_
