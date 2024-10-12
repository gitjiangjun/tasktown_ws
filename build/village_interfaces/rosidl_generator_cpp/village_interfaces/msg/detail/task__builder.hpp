// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from village_interfaces:msg/Task.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__MSG__DETAIL__TASK__BUILDER_HPP_
#define VILLAGE_INTERFACES__MSG__DETAIL__TASK__BUILDER_HPP_

#include "village_interfaces/msg/detail/task__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace village_interfaces
{

namespace msg
{

namespace builder
{

class Init_Task_image
{
public:
  explicit Init_Task_image(::village_interfaces::msg::Task & msg)
  : msg_(msg)
  {}
  ::village_interfaces::msg::Task image(::village_interfaces::msg::Task::_image_type arg)
  {
    msg_.image = std::move(arg);
    return std::move(msg_);
  }

private:
  ::village_interfaces::msg::Task msg_;
};

class Init_Task_content
{
public:
  Init_Task_content()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Task_image content(::village_interfaces::msg::Task::_content_type arg)
  {
    msg_.content = std::move(arg);
    return Init_Task_image(msg_);
  }

private:
  ::village_interfaces::msg::Task msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::village_interfaces::msg::Task>()
{
  return village_interfaces::msg::builder::Init_Task_content();
}

}  // namespace village_interfaces

#endif  // VILLAGE_INTERFACES__MSG__DETAIL__TASK__BUILDER_HPP_
