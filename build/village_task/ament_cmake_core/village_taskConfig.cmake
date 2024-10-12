# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_village_task_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED village_task_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(village_task_FOUND FALSE)
  elseif(NOT village_task_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(village_task_FOUND FALSE)
  endif()
  return()
endif()
set(_village_task_CONFIG_INCLUDED TRUE)

# output package information
if(NOT village_task_FIND_QUIETLY)
  message(STATUS "Found village_task: 0.0.0 (${village_task_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'village_task' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${village_task_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(village_task_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${village_task_DIR}/${_extra}")
endforeach()
