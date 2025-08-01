set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

set(cpp_sources "cpu.cpp" "register_set.cpp")

set(c_sources "")
set(cpu_module
    "${cpu_MODULE_ROOT}/cpu.h"
    "${cpu_MODULE_ROOT}/executor.h"
    "${cpu_MODULE_ROOT}/register.h"
    "${cpu_MODULE_ROOT}/register_functionoid.h"
    "${cpu_MODULE_ROOT}/opcode_handler.h"
    "${cpu_MODULE_ROOT}/opcode_tags.h"
    "${cpu_MODULE_ROOT}/register_set.h"
    "${cpu_MODULE_ROOT}/register_set_functionoid.h")

set(cpu_internal_register_module
    "${cpu_MODULE_ROOT}/internal/register/register_flag_operations.h"
    "${cpu_MODULE_ROOT}/internal/register/register_arithmetic_operators.h"
    "${cpu_MODULE_ROOT}/internal/register/register_bitwise_operators.h"
    "${cpu_MODULE_ROOT}/internal/register/register_comparison_operators.h")

set(cpu_internal_opcode_module
    "${cpu_MODULE_ROOT}/internal/opcode/opcode_handler_fwd_decls.h"
    "${cpu_MODULE_ROOT}/internal/opcode/8bit_load.h"
    "${cpu_MODULE_ROOT}/internal/opcode/16bit_load.h"
    "${cpu_MODULE_ROOT}/internal/opcode/8bit_arithmetic.h"
    "${cpu_MODULE_ROOT}/internal/opcode/16bit_arithmetic.h"
    "${cpu_MODULE_ROOT}/internal/opcode/rotate_and_shift.h"
    "${cpu_MODULE_ROOT}/internal/opcode/jump.h"
    "${cpu_MODULE_ROOT}/internal/opcode/single_bit.h")

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
         ${cpu_internal_register_module}
         ${cpu_internal_opcode_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

target_link_libraries(cpu memory types utility)

if(MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
