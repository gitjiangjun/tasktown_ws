#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "village_interfaces::village_interfaces__rosidl_generator_c" for configuration "RelWithDebInfo"
set_property(TARGET village_interfaces::village_interfaces__rosidl_generator_c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(village_interfaces::village_interfaces__rosidl_generator_c PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libvillage_interfaces__rosidl_generator_c.so"
  IMPORTED_SONAME_RELWITHDEBINFO "libvillage_interfaces__rosidl_generator_c.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS village_interfaces::village_interfaces__rosidl_generator_c )
list(APPEND _IMPORT_CHECK_FILES_FOR_village_interfaces::village_interfaces__rosidl_generator_c "${_IMPORT_PREFIX}/lib/libvillage_interfaces__rosidl_generator_c.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
