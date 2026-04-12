// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "pose_once/srv/detail/trigger_pose_estimation__rosidl_typesupport_introspection_c.h"
#include "pose_once/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "pose_once/srv/detail/trigger_pose_estimation__functions.h"
#include "pose_once/srv/detail/trigger_pose_estimation__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pose_once__srv__TriggerPoseEstimation_Request__init(message_memory);
}

void pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_fini_function(void * message_memory)
{
  pose_once__srv__TriggerPoseEstimation_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pose_once__srv__TriggerPoseEstimation_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_members = {
  "pose_once__srv",  // message namespace
  "TriggerPoseEstimation_Request",  // message name
  1,  // number of fields
  sizeof(pose_once__srv__TriggerPoseEstimation_Request),
  pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_member_array,  // message members
  pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_type_support_handle = {
  0,
  &pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pose_once
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Request)() {
  if (!pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_type_support_handle.typesupport_identifier) {
    pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &pose_once__srv__TriggerPoseEstimation_Request__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "pose_once/srv/detail/trigger_pose_estimation__rosidl_typesupport_introspection_c.h"
// already included above
// #include "pose_once/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "pose_once/srv/detail/trigger_pose_estimation__functions.h"
// already included above
// #include "pose_once/srv/detail/trigger_pose_estimation__struct.h"


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  pose_once__srv__TriggerPoseEstimation_Response__init(message_memory);
}

void pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_fini_function(void * message_memory)
{
  pose_once__srv__TriggerPoseEstimation_Response__fini(message_memory);
}

size_t pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__size_function__TriggerPoseEstimation_Response__pose(
  const void * untyped_member)
{
  (void)untyped_member;
  return 16;
}

const void * pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_const_function__TriggerPoseEstimation_Response__pose(
  const void * untyped_member, size_t index)
{
  const double * member =
    (const double *)(untyped_member);
  return &member[index];
}

void * pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_function__TriggerPoseEstimation_Response__pose(
  void * untyped_member, size_t index)
{
  double * member =
    (double *)(untyped_member);
  return &member[index];
}

void pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__fetch_function__TriggerPoseEstimation_Response__pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_const_function__TriggerPoseEstimation_Response__pose(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__assign_function__TriggerPoseEstimation_Response__pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_function__TriggerPoseEstimation_Response__pose(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_member_array[3] = {
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    16,  // array size
    false,  // is upper bound
    offsetof(pose_once__srv__TriggerPoseEstimation_Response, pose),  // bytes offset in struct
    NULL,  // default value
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__size_function__TriggerPoseEstimation_Response__pose,  // size() function pointer
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_const_function__TriggerPoseEstimation_Response__pose,  // get_const(index) function pointer
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__get_function__TriggerPoseEstimation_Response__pose,  // get(index) function pointer
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__fetch_function__TriggerPoseEstimation_Response__pose,  // fetch(index, &value) function pointer
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__assign_function__TriggerPoseEstimation_Response__pose,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pose_once__srv__TriggerPoseEstimation_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(pose_once__srv__TriggerPoseEstimation_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_members = {
  "pose_once__srv",  // message namespace
  "TriggerPoseEstimation_Response",  // message name
  3,  // number of fields
  sizeof(pose_once__srv__TriggerPoseEstimation_Response),
  pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_member_array,  // message members
  pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_type_support_handle = {
  0,
  &pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pose_once
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Response)() {
  if (!pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_type_support_handle.typesupport_identifier) {
    pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &pose_once__srv__TriggerPoseEstimation_Response__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "pose_once/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "pose_once/srv/detail/trigger_pose_estimation__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_members = {
  "pose_once__srv",  // service namespace
  "TriggerPoseEstimation",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Request_message_type_support_handle,
  NULL  // response message
  // pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_Response_message_type_support_handle
};

static rosidl_service_type_support_t pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_type_support_handle = {
  0,
  &pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_pose_once
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation)() {
  if (!pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_type_support_handle.typesupport_identifier) {
    pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pose_once, srv, TriggerPoseEstimation_Response)()->data;
  }

  return &pose_once__srv__detail__trigger_pose_estimation__rosidl_typesupport_introspection_c__TriggerPoseEstimation_service_type_support_handle;
}
