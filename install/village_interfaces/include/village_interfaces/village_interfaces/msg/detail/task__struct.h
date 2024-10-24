﻿// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from village_interfaces:msg/Task.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__MSG__DETAIL__TASK__STRUCT_H_
#define VILLAGE_INTERFACES__MSG__DETAIL__TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'content'
#include "rosidl_runtime_c/string.h"
// Member 'image'
#include "sensor_msgs/msg/detail/image__struct.h"

/// Struct defined in msg/Task in the package village_interfaces.
/**
  * 调用ros2原始数据类型
 */
typedef struct village_interfaces__msg__Task
{
  rosidl_runtime_c__String content;
  /// 调用已有数据类型
  sensor_msgs__msg__Image image;
} village_interfaces__msg__Task;

// Struct for a sequence of village_interfaces__msg__Task.
typedef struct village_interfaces__msg__Task__Sequence
{
  village_interfaces__msg__Task * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} village_interfaces__msg__Task__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACES__MSG__DETAIL__TASK__STRUCT_H_
