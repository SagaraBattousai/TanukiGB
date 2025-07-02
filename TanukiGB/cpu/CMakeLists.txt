
set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

set(cpp_sources 
  "cpu.cpp" 
  "cpu_register_8bit.cpp" 
  "cpu_register_16bit.cpp"
  "cpu_register_map.cpp"
  )

set(c_sources "")
set(cpu_module
  "${cpu_MODULE_ROOT}/cpu.h"
  "${cpu_MODULE_ROOT}/cpu_register.h"
  "${cpu_MODULE_ROOT}/cpu_register_8bit.h"
  "${cpu_MODULE_ROOT}/cpu_register_16bit.h"
  "${cpu_MODULE_ROOT}/cpu_register_map.h"
  )

add_library(cpu SHARED ${cpp_sources} ${c_sources})

target_sources(cpu PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${cpu_module}
  "${MODULE_ROOT}/_TanukiGB_config.h"
  )

target_link_libraries(cpu memory types)

if (MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
