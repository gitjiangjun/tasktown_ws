// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from village_interfaces:srv/UpdateTask.idl
// generated code does not contain a copyright notice

#ifndef VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__TRAITS_HPP_
#define VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "village_interfaces/srv/detail/update_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace village_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const UpdateTask_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: tasks
  {
    if (msg.tasks.size() == 0) {
      out << "tasks: []";
    } else {
      out << "tasks: [";
      size_t pending_items = msg.tasks.size();
      for (auto item : msg.tasks) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UpdateTask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tasks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tasks.size() == 0) {
      out << "tasks: []\n";
    } else {
      out << "tasks:\n";
      for (auto item : msg.tasks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UpdateTask_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace village_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use village_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const village_interfaces::srv::UpdateTask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  village_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use village_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const village_interfaces::srv::UpdateTask_Request & msg)
{
  return village_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<village_interfaces::srv::UpdateTask_Request>()
{
  return "village_interfaces::srv::UpdateTask_Request";
}

template<>
inline const char * name<village_interfaces::srv::UpdateTask_Request>()
{
  return "village_interfaces/srv/UpdateTask_Request";
}

template<>
struct has_fixed_size<village_interfaces::srv::UpdateTask_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<village_interfaces::srv::UpdateTask_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<village_interfaces::srv::UpdateTask_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace village_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const UpdateTask_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: tasks_result
  {
    if (msg.tasks_result.size() == 0) {
      out << "tasks_result: []";
    } else {
      out << "tasks_result: [";
      size_t pending_items = msg.tasks_result.size();
      for (auto item : msg.tasks_result) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const UpdateTask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tasks_result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tasks_result.size() == 0) {
      out << "tasks_result: []\n";
    } else {
      out << "tasks_result:\n";
      for (auto item : msg.tasks_result) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const UpdateTask_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace village_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use village_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const village_interfaces::srv::UpdateTask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  village_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use village_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const village_interfaces::srv::UpdateTask_Response & msg)
{
  return village_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<village_interfaces::srv::UpdateTask_Response>()
{
  return "village_interfaces::srv::UpdateTask_Response";
}

template<>
inline const char * name<village_interfaces::srv::UpdateTask_Response>()
{
  return "village_interfaces/srv/UpdateTask_Response";
}

template<>
struct has_fixed_size<village_interfaces::srv::UpdateTask_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<village_interfaces::srv::UpdateTask_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<village_interfaces::srv::UpdateTask_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<village_interfaces::srv::UpdateTask>()
{
  return "village_interfaces::srv::UpdateTask";
}

template<>
inline const char * name<village_interfaces::srv::UpdateTask>()
{
  return "village_interfaces/srv/UpdateTask";
}

template<>
struct has_fixed_size<village_interfaces::srv::UpdateTask>
  : std::integral_constant<
    bool,
    has_fixed_size<village_interfaces::srv::UpdateTask_Request>::value &&
    has_fixed_size<village_interfaces::srv::UpdateTask_Response>::value
  >
{
};

template<>
struct has_bounded_size<village_interfaces::srv::UpdateTask>
  : std::integral_constant<
    bool,
    has_bounded_size<village_interfaces::srv::UpdateTask_Request>::value &&
    has_bounded_size<village_interfaces::srv::UpdateTask_Response>::value
  >
{
};

template<>
struct is_service<village_interfaces::srv::UpdateTask>
  : std::true_type
{
};

template<>
struct is_service_request<village_interfaces::srv::UpdateTask_Request>
  : std::true_type
{
};

template<>
struct is_service_response<village_interfaces::srv::UpdateTask_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VILLAGE_INTERFACES__SRV__DETAIL__UPDATE_TASK__TRAITS_HPP_
