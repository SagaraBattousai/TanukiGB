
set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

set(cpp_sources "cpu.cpp" "register.cpp")
set(c_sources "")
set(cpu_module
  "${cpu_MODULE_ROOT}/cpu.h"
  )

add_library(cpu SHARED ${cpp_sources} ${c_sources})

target_sources(cpu PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${cpu_module}
  "${MODULE_ROOT}/_TanukiGB_config.h"
  )

if (MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
