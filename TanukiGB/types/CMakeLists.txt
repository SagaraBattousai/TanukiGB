set(types_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/types")

add_library(types INTERFACE)

target_sources(types PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES #"${MODULE_ROOT}/_TanukiGB_config.h"
    "${types_MODULE_ROOT}/types.h"
  )
