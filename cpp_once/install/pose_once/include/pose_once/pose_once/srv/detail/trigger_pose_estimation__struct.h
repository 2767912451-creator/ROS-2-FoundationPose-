// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice

#ifndef POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_H_
#define POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/TriggerPoseEstimation in the package pose_once.
typedef struct pose_once__srv__TriggerPoseEstimation_Request
{
  uint8_t structure_needs_at_least_one_member;
} pose_once__srv__TriggerPoseEstimation_Request;

// Struct for a sequence of pose_once__srv__TriggerPoseEstimation_Request.
typedef struct pose_once__srv__TriggerPoseEstimation_Request__Sequence
{
  pose_once__srv__TriggerPoseEstimation_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pose_once__srv__TriggerPoseEstimation_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/TriggerPoseEstimation in the package pose_once.
typedef struct pose_once__srv__TriggerPoseEstimation_Response
{
  double pose[16];
  bool success;
  rosidl_runtime_c__String message;
} pose_once__srv__TriggerPoseEstimation_Response;

// Struct for a sequence of pose_once__srv__TriggerPoseEstimation_Response.
typedef struct pose_once__srv__TriggerPoseEstimation_Response__Sequence
{
  pose_once__srv__TriggerPoseEstimation_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} pose_once__srv__TriggerPoseEstimation_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // POSE_ONCE__SRV__DETAIL__TRIGGER_POSE_ESTIMATION__STRUCT_H_
