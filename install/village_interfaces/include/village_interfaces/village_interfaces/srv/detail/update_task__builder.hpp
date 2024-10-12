// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interfaces:srv/UpdateTask.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__BUILDER_HPP_
#define VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "village_interfaces/srv/detail/update_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_UpdateTask_Request_tasks
{
public:
  Init_UpdateTask_Request_tasks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::UpdateTask_Request tasks(::village_interfaces::srv::UpdateTask_Request::_tasks_type arg)
  {
    msg_.tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::UpdateTask_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::UpdateTask_Request>()
{
  return village_interfaces::srv::builder::Init_UpdateTask_Request_tasks();
}

}  // namespace village_interfaces


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_UpdateTask_Response_tasks_result
{
public:
  Init_UpdateTask_Response_tasks_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::UpdateTask_Response tasks_result(::village_interfaces::srv::UpdateTask_Response::_tasks_result_type arg)
  {
    msg_.tasks_result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::UpdateTask_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::UpdateTask_Response>()
{
  return village_interfaces::srv::builder::Init_UpdateTask_Response_tasks_result();
}

}  // namespace village_interfaces

#endif  // VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__BUILDER_HPP_
