// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interfaces:srv/TaskUpdate.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__SRV__DETAIL__TASK_UPDATE__BUILDER_HPP_
#define VILLAGE_INTERFACES__SRV__DETAIL__TASK_UPDATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "village_interfaces/srv/detail/task_update__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_TaskUpdate_Request_tasks
{
public:
  Init_TaskUpdate_Request_tasks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::TaskUpdate_Request tasks(::village_interfaces::srv::TaskUpdate_Request::_tasks_type arg)
  {
    msg_.tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::TaskUpdate_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::TaskUpdate_Request>()
{
  return village_interfaces::srv::builder::Init_TaskUpdate_Request_tasks();
}

}  // namespace village_interfaces


namespace village_interfaces
{

namespace srv
{

namespace builder
{

class Init_TaskUpdate_Response_success
{
public:
  Init_TaskUpdate_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::village_interfaces::srv::TaskUpdate_Response success(::village_interfaces::srv::TaskUpdate_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::srv::TaskUpdate_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::srv::TaskUpdate_Response>()
{
  return village_interfaces::srv::builder::Init_TaskUpdate_Response_success();
}

}  // namespace village_interfaces

#endif  // VILLAGE_INTERFACES__SRV__DETAIL__TASK_UPDATE__BUILDER_HPP_
