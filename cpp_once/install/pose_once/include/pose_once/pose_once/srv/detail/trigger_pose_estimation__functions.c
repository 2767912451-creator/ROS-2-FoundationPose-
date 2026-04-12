// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from pose_once:srv/TriggerPoseEstimation.idl
// generated code does not contain a copyright notice
#include "pose_once/srv/detail/trigger_pose_estimation__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
pose_once__srv__TriggerPoseEstimation_Request__init(pose_once__srv__TriggerPoseEstimation_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
pose_once__srv__TriggerPoseEstimation_Request__fini(pose_once__srv__TriggerPoseEstimation_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
pose_once__srv__TriggerPoseEstimation_Request__are_equal(const pose_once__srv__TriggerPoseEstimation_Request * lhs, const pose_once__srv__TriggerPoseEstimation_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
pose_once__srv__TriggerPoseEstimation_Request__copy(
  const pose_once__srv__TriggerPoseEstimation_Request * input,
  pose_once__srv__TriggerPoseEstimation_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

pose_once__srv__TriggerPoseEstimation_Request *
pose_once__srv__TriggerPoseEstimation_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Request * msg = (pose_once__srv__TriggerPoseEstimation_Request *)allocator.allocate(sizeof(pose_once__srv__TriggerPoseEstimation_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pose_once__srv__TriggerPoseEstimation_Request));
  bool success = pose_once__srv__TriggerPoseEstimation_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pose_once__srv__TriggerPoseEstimation_Request__destroy(pose_once__srv__TriggerPoseEstimation_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pose_once__srv__TriggerPoseEstimation_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pose_once__srv__TriggerPoseEstimation_Request__Sequence__init(pose_once__srv__TriggerPoseEstimation_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Request * data = NULL;

  if (size) {
    data = (pose_once__srv__TriggerPoseEstimation_Request *)allocator.zero_allocate(size, sizeof(pose_once__srv__TriggerPoseEstimation_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pose_once__srv__TriggerPoseEstimation_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pose_once__srv__TriggerPoseEstimation_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
pose_once__srv__TriggerPoseEstimation_Request__Sequence__fini(pose_once__srv__TriggerPoseEstimation_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      pose_once__srv__TriggerPoseEstimation_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

pose_once__srv__TriggerPoseEstimation_Request__Sequence *
pose_once__srv__TriggerPoseEstimation_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Request__Sequence * array = (pose_once__srv__TriggerPoseEstimation_Request__Sequence *)allocator.allocate(sizeof(pose_once__srv__TriggerPoseEstimation_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pose_once__srv__TriggerPoseEstimation_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pose_once__srv__TriggerPoseEstimation_Request__Sequence__destroy(pose_once__srv__TriggerPoseEstimation_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pose_once__srv__TriggerPoseEstimation_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pose_once__srv__TriggerPoseEstimation_Request__Sequence__are_equal(const pose_once__srv__TriggerPoseEstimation_Request__Sequence * lhs, const pose_once__srv__TriggerPoseEstimation_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pose_once__srv__TriggerPoseEstimation_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pose_once__srv__TriggerPoseEstimation_Request__Sequence__copy(
  const pose_once__srv__TriggerPoseEstimation_Request__Sequence * input,
  pose_once__srv__TriggerPoseEstimation_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pose_once__srv__TriggerPoseEstimation_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pose_once__srv__TriggerPoseEstimation_Request * data =
      (pose_once__srv__TriggerPoseEstimation_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pose_once__srv__TriggerPoseEstimation_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pose_once__srv__TriggerPoseEstimation_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pose_once__srv__TriggerPoseEstimation_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
pose_once__srv__TriggerPoseEstimation_Response__init(pose_once__srv__TriggerPoseEstimation_Response * msg)
{
  if (!msg) {
    return false;
  }
  // pose
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    pose_once__srv__TriggerPoseEstimation_Response__fini(msg);
    return false;
  }
  return true;
}

void
pose_once__srv__TriggerPoseEstimation_Response__fini(pose_once__srv__TriggerPoseEstimation_Response * msg)
{
  if (!msg) {
    return;
  }
  // pose
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
pose_once__srv__TriggerPoseEstimation_Response__are_equal(const pose_once__srv__TriggerPoseEstimation_Response * lhs, const pose_once__srv__TriggerPoseEstimation_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pose
  for (size_t i = 0; i < 16; ++i) {
    if (lhs->pose[i] != rhs->pose[i]) {
      return false;
    }
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
pose_once__srv__TriggerPoseEstimation_Response__copy(
  const pose_once__srv__TriggerPoseEstimation_Response * input,
  pose_once__srv__TriggerPoseEstimation_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // pose
  for (size_t i = 0; i < 16; ++i) {
    output->pose[i] = input->pose[i];
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

pose_once__srv__TriggerPoseEstimation_Response *
pose_once__srv__TriggerPoseEstimation_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Response * msg = (pose_once__srv__TriggerPoseEstimation_Response *)allocator.allocate(sizeof(pose_once__srv__TriggerPoseEstimation_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(pose_once__srv__TriggerPoseEstimation_Response));
  bool success = pose_once__srv__TriggerPoseEstimation_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
pose_once__srv__TriggerPoseEstimation_Response__destroy(pose_once__srv__TriggerPoseEstimation_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    pose_once__srv__TriggerPoseEstimation_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
pose_once__srv__TriggerPoseEstimation_Response__Sequence__init(pose_once__srv__TriggerPoseEstimation_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Response * data = NULL;

  if (size) {
    data = (pose_once__srv__TriggerPoseEstimation_Response *)allocator.zero_allocate(size, sizeof(pose_once__srv__TriggerPoseEstimation_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = pose_once__srv__TriggerPoseEstimation_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        pose_once__srv__TriggerPoseEstimation_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
pose_once__srv__TriggerPoseEstimation_Response__Sequence__fini(pose_once__srv__TriggerPoseEstimation_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      pose_once__srv__TriggerPoseEstimation_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

pose_once__srv__TriggerPoseEstimation_Response__Sequence *
pose_once__srv__TriggerPoseEstimation_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  pose_once__srv__TriggerPoseEstimation_Response__Sequence * array = (pose_once__srv__TriggerPoseEstimation_Response__Sequence *)allocator.allocate(sizeof(pose_once__srv__TriggerPoseEstimation_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = pose_once__srv__TriggerPoseEstimation_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
pose_once__srv__TriggerPoseEstimation_Response__Sequence__destroy(pose_once__srv__TriggerPoseEstimation_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    pose_once__srv__TriggerPoseEstimation_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
pose_once__srv__TriggerPoseEstimation_Response__Sequence__are_equal(const pose_once__srv__TriggerPoseEstimation_Response__Sequence * lhs, const pose_once__srv__TriggerPoseEstimation_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!pose_once__srv__TriggerPoseEstimation_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
pose_once__srv__TriggerPoseEstimation_Response__Sequence__copy(
  const pose_once__srv__TriggerPoseEstimation_Response__Sequence * input,
  pose_once__srv__TriggerPoseEstimation_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(pose_once__srv__TriggerPoseEstimation_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    pose_once__srv__TriggerPoseEstimation_Response * data =
      (pose_once__srv__TriggerPoseEstimation_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!pose_once__srv__TriggerPoseEstimation_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          pose_once__srv__TriggerPoseEstimation_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!pose_once__srv__TriggerPoseEstimation_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
