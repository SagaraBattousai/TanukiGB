
set(memory_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/memory")
# set(internal_memory_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/internal/memory")

set(cpp_sources "memory.cpp" "bootrom.cpp")
set(c_sources "")
set(memory_module 
  "${memory_MODULE_ROOT}/bootrom.h"
  "${memory_MODULE_ROOT}/memory.h" # Could move to internal but....
  )
# set(internal_memory_module
#   "${internal_memory_MODULE_ROOT}/memory.h"
#   )

add_library(memory SHARED ${cpp_sources} ${c_sources})

target_sources(memory PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${memory_module}
  "${MODULE_ROOT}/_TanukiGB_config.h"
  )

# target_sources(memory PRIVATE
#   FILE_SET private_headers
#   TYPE HEADERS
#   BASE_DIRS ${MODULE_ROOT}
#   FILES ${internal_memory_module}
#   )

if (MSVC)
  target_compile_definitions(memory PRIVATE TANUKIGB_BUILD_DLL)
endif()
