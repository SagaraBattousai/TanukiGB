set(utility_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/utility")

add_library(utility INTERFACE)

set_target_properties(utility PROPERTIES CXX_STANDARD 20)

target_sources(utility PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES
    "${utility_MODULE_ROOT}/enum_utils.h"
    "${utility_MODULE_ROOT}/pimpl.h"
  )
