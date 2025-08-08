
# TODO: If deemed neccisary

set(opcode_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu/opcode")

set(cpp_sources "")
set(c_sources "")

set(opcode_module
    "${opcode_MODULE_ROOT}/opcode.h"
    "${opcode_MODULE_ROOT}/opcode_ops.h"
    "${opcode_MODULE_ROOT}/opcode_type_traits.h"
    "${opcode_MODULE_ROOT}/opcode_functionoid.h"
    "${opcode_MODULE_ROOT}/opcode_set.h"
    "${opcode_MODULE_ROOT}/opcode_set_functionoid.h")

set(opcode_internal_opcode_module
    "${opcode_MODULE_ROOT}/internal/opcode_flag_operations.h"
    "${opcode_MODULE_ROOT}/internal/opcode_arithmetic_operators.h"
    "${opcode_MODULE_ROOT}/internal/opcode_bitwise_operators.h"
    "${opcode_MODULE_ROOT}/internal/opcode_comparison_operators.h")

add_library(opcode OBJECT ${cpp_sources} ${c_sources})

target_sources(
  opcode
  PUBLIC FILE_SET
         HEADERS
         TYPE
         HEADERS
         BASE_DIRS
         ${MODULE_ROOT}
         FILES
         ${opcode_module}
         ${opcode_internal_opcode_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

target_link_libraries(opcode types utility)

# Cant prepend cpu to folder path as it's name is already in use (for a library)
set_target_properties(opcode PROPERTIES FOLDER "${ROOT_FOLDER_NAME}/libs")

if(MSVC)
  target_compile_definitions(opcode PRIVATE TANUKIGB_BUILD_DLL)
endif()
