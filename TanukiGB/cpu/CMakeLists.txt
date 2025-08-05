set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

set(cpp_sources "cpu.cpp")

set(c_sources "")
set(cpu_module
    "${cpu_MODULE_ROOT}/cpu.h" 
    # TEMP
    "${cpu_MODULE_ROOT}/register_tags.h"
    "${cpu_MODULE_ROOT}/executor.h"
    "${cpu_MODULE_ROOT}/opcode_handler.h" "${cpu_MODULE_ROOT}/opcode_tags.h")

set(cpu_internal_opcode_module
    "${cpu_MODULE_ROOT}/internal/opcode_handler_fwd_decls.h"
    "${cpu_MODULE_ROOT}/internal/8bit_load.h"
    "${cpu_MODULE_ROOT}/internal/16bit_load.h"
    "${cpu_MODULE_ROOT}/internal/8bit_arithmetic.h"
    "${cpu_MODULE_ROOT}/internal/16bit_arithmetic.h"
    "${cpu_MODULE_ROOT}/internal/rotate_and_shift.h"
    "${cpu_MODULE_ROOT}/internal/jump.h"
    "${cpu_MODULE_ROOT}/internal/single_bit.h")

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
         ${cpu_internal_opcode_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

add_subdirectory(register)
target_link_libraries(cpu memory types utility register)

if(MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
