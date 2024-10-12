// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interfaces:srv/TaskAssign.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__SRV__DETAIL__TASK_ASSIGN__BUILDER_HPP_
#define VILLAGE_INTERFACES__SRV__DETAIL__TASK_ASSIGN__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "village_interfaces/srv/detail/task_assign__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_TaskAssign_Request_tasks
{
public:
  Init_TaskAssign_Request_tasks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::TaskAssign_Request tasks(::village_interfaces::srv::TaskAssign_Request::_tasks_type arg)
  {
    msg_.tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::TaskAssign_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::TaskAssign_Request>()
{
  return village_interfaces::srv::builder::Init_TaskAssign_Request_tasks();
}

}  // namespace village_interfaces


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_TaskAssign_Response_task_result
{
public:
  Init_TaskAssign_Response_task_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::TaskAssign_Response task_result(::village_interfaces::srv::TaskAssign_Response::_task_result_type arg)
  {
    msg_.task_result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::TaskAssign_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::TaskAssign_Response>()
{
  return village_interfaces::srv::builder::Init_TaskAssign_Response_task_result();
}

}  // namespace village_interfaces

#endif  // VILLAGE_INTERFACES__SRV__DETAIL__TASK_ASSIGN__BUILDER_HPP_
