// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from village_interfaces:srv/TaskAssign.idl
// generated code does not contain a copyright notice
#include "village_interfaces/srv/detail/task_assign__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `tasks`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
village_interfaces__srv__TaskAssign_Request__init(village_interfaces__srv__TaskAssign_Request * msg)
{
  if (!msg) {
    return false;
  }
  // tasks
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->tasks, 0)) {
    village_interfaces__srv__TaskAssign_Request__fini(msg);
    return false;
  }
  return true;
}

void
village_interfaces__srv__TaskAssign_Request__fini(village_interfaces__srv__TaskAssign_Request * msg)
{
  if (!msg) {
    return;
  }
  // tasks
  rosidl_runtime_c__int32__Sequence__fini(&msg->tasks);
}

bool
village_interfaces__srv__TaskAssign_Request__are_equal(const village_interfaces__srv__TaskAssign_Request * lhs, const village_interfaces__srv__TaskAssign_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tasks
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->tasks), &(rhs->tasks)))
  {
    return false;
  }
  return true;
}

bool
village_interfaces__srv__TaskAssign_Request__copy(
  const village_interfaces__srv__TaskAssign_Request * input,
  village_interfaces__srv__TaskAssign_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // tasks
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->tasks), &(output->tasks)))
  {
    return false;
  }
  return true;
}

village_interfaces__srv__TaskAssign_Request *
village_interfaces__srv__TaskAssign_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Request * msg = (village_interfaces__srv__TaskAssign_Request *)allocator.allocate(sizeof(village_interfaces__srv__TaskAssign_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interfaces__srv__TaskAssign_Request));
  bool success = village_interfaces__srv__TaskAssign_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interfaces__srv__TaskAssign_Request__destroy(village_interfaces__srv__TaskAssign_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interfaces__srv__TaskAssign_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interfaces__srv__TaskAssign_Request__Sequence__init(village_interfaces__srv__TaskAssign_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Request * data = NULL;

  if (size) {
    data = (village_interfaces__srv__TaskAssign_Request *)allocator.zero_allocate(size, sizeof(village_interfaces__srv__TaskAssign_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interfaces__srv__TaskAssign_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interfaces__srv__TaskAssign_Request__fini(&data[i - 1]);
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
village_interfaces__srv__TaskAssign_Request__Sequence__fini(village_interfaces__srv__TaskAssign_Request__Sequence * array)
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
      village_interfaces__srv__TaskAssign_Request__fini(&array->data[i]);
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

village_interfaces__srv__TaskAssign_Request__Sequence *
village_interfaces__srv__TaskAssign_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Request__Sequence * array = (village_interfaces__srv__TaskAssign_Request__Sequence *)allocator.allocate(sizeof(village_interfaces__srv__TaskAssign_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interfaces__srv__TaskAssign_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interfaces__srv__TaskAssign_Request__Sequence__destroy(village_interfaces__srv__TaskAssign_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interfaces__srv__TaskAssign_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interfaces__srv__TaskAssign_Request__Sequence__are_equal(const village_interfaces__srv__TaskAssign_Request__Sequence * lhs, const village_interfaces__srv__TaskAssign_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interfaces__srv__TaskAssign_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interfaces__srv__TaskAssign_Request__Sequence__copy(
  const village_interfaces__srv__TaskAssign_Request__Sequence * input,
  village_interfaces__srv__TaskAssign_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interfaces__srv__TaskAssign_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    village_interfaces__srv__TaskAssign_Request * data =
      (village_interfaces__srv__TaskAssign_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interfaces__srv__TaskAssign_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          village_interfaces__srv__TaskAssign_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interfaces__srv__TaskAssign_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `task_result`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
village_interfaces__srv__TaskAssign_Response__init(village_interfaces__srv__TaskAssign_Response * msg)
{
  if (!msg) {
    return false;
  }
  // task_result
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->task_result, 0)) {
    village_interfaces__srv__TaskAssign_Response__fini(msg);
    return false;
  }
  return true;
}

void
village_interfaces__srv__TaskAssign_Response__fini(village_interfaces__srv__TaskAssign_Response * msg)
{
  if (!msg) {
    return;
  }
  // task_result
  rosidl_runtime_c__int32__Sequence__fini(&msg->task_result);
}

bool
village_interfaces__srv__TaskAssign_Response__are_equal(const village_interfaces__srv__TaskAssign_Response * lhs, const village_interfaces__srv__TaskAssign_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // task_result
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->task_result), &(rhs->task_result)))
  {
    return false;
  }
  return true;
}

bool
village_interfaces__srv__TaskAssign_Response__copy(
  const village_interfaces__srv__TaskAssign_Response * input,
  village_interfaces__srv__TaskAssign_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // task_result
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->task_result), &(output->task_result)))
  {
    return false;
  }
  return true;
}

village_interfaces__srv__TaskAssign_Response *
village_interfaces__srv__TaskAssign_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Response * msg = (village_interfaces__srv__TaskAssign_Response *)allocator.allocate(sizeof(village_interfaces__srv__TaskAssign_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interfaces__srv__TaskAssign_Response));
  bool success = village_interfaces__srv__TaskAssign_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interfaces__srv__TaskAssign_Response__destroy(village_interfaces__srv__TaskAssign_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interfaces__srv__TaskAssign_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interfaces__srv__TaskAssign_Response__Sequence__init(village_interfaces__srv__TaskAssign_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Response * data = NULL;

  if (size) {
    data = (village_interfaces__srv__TaskAssign_Response *)allocator.zero_allocate(size, sizeof(village_interfaces__srv__TaskAssign_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interfaces__srv__TaskAssign_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interfaces__srv__TaskAssign_Response__fini(&data[i - 1]);
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
village_interfaces__srv__TaskAssign_Response__Sequence__fini(village_interfaces__srv__TaskAssign_Response__Sequence * array)
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
      village_interfaces__srv__TaskAssign_Response__fini(&array->data[i]);
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

village_interfaces__srv__TaskAssign_Response__Sequence *
village_interfaces__srv__TaskAssign_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__TaskAssign_Response__Sequence * array = (village_interfaces__srv__TaskAssign_Response__Sequence *)allocator.allocate(sizeof(village_interfaces__srv__TaskAssign_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interfaces__srv__TaskAssign_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interfaces__srv__TaskAssign_Response__Sequence__destroy(village_interfaces__srv__TaskAssign_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interfaces__srv__TaskAssign_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interfaces__srv__TaskAssign_Response__Sequence__are_equal(const village_interfaces__srv__TaskAssign_Response__Sequence * lhs, const village_interfaces__srv__TaskAssign_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interfaces__srv__TaskAssign_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interfaces__srv__TaskAssign_Response__Sequence__copy(
  const village_interfaces__srv__TaskAssign_Response__Sequence * input,
  village_interfaces__srv__TaskAssign_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interfaces__srv__TaskAssign_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    village_interfaces__srv__TaskAssign_Response * data =
      (village_interfaces__srv__TaskAssign_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interfaces__srv__TaskAssign_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          village_interfaces__srv__TaskAssign_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interfaces__srv__TaskAssign_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
