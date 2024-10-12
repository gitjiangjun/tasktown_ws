// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from village_interfaces:srv/UpdateTask.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__STRUCT_H_
#define VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'tasks'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/UpdateTask in the package village_interfaces.
typedef struct village_interfaces__srv__UpdateTask_Request
{
  rosidl_runtime_c__int32__Sequence tasks;
} village_interfaces__srv__UpdateTask_Request;

// Struct for a sequence of village_interfaces__srv__UpdateTask_Request.
typedef struct village_interfaces__srv__UpdateTask_Request__Sequence
{
  village_interfaces__srv__UpdateTask_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} village_interfaces__srv__UpdateTask_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'tasks_result'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/UpdateTask in the package village_interfaces.
typedef struct village_interfaces__srv__UpdateTask_Response
{
  rosidl_runtime_c__int32__Sequence tasks_result;
} village_interfaces__srv__UpdateTask_Response;

// Struct for a sequence of village_interfaces__srv__UpdateTask_Response.
typedef struct village_interfaces__srv__UpdateTask_Response__Sequence
{
  village_interfaces__srv__UpdateTask_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} village_interfaces__srv__UpdateTask_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__STRUCT_H_
