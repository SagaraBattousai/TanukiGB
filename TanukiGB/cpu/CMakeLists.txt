set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

set(cpp_sources "cpu.cpp" "register_set.cpp")

set(c_sources "")
set(cpu_module 
  "${cpu_MODULE_ROOT}/cpu.h" 
  "${cpu_MODULE_ROOT}/register.h"
  "${cpu_MODULE_ROOT}/register_set.h"
  "${cpu_MODULE_ROOT}/register_set_functionoid.h"
  )

set(cpu_private_module "opcode_handler.h")

add_library(cpu SHARED ${cpp_sources} ${c_sources})

target_sources(
  cpu
  PUBLIC FILE_SET
         HEADERS
         TYPE
         HEADERS
         BASE_DIRS
         ${MODULE_ROOT}
         FILES
         ${cpu_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

target_sources(cpu PRIVATE FILE_SET private_HEADERS TYPE HEADERS FILES
                           ${cpu_private_module})

target_link_libraries(cpu memory types utility)

if(MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
