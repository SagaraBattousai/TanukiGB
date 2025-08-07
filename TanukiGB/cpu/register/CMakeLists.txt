set(register_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu/register")

set(cpp_sources "register_set.cpp")

set(c_sources "")
set(register_module
    "${register_MODULE_ROOT}/register.h"
    "${register_MODULE_ROOT}/register_ops.h"
    "${register_MODULE_ROOT}/register_type_traits.h"
    "${register_MODULE_ROOT}/register_functionoid.h"
    "${register_MODULE_ROOT}/register_set.h"
    "${register_MODULE_ROOT}/register_set_functionoid.h")

set(register_internal_register_module
    "${register_MODULE_ROOT}/internal/register_flag_operations.h"
    "${register_MODULE_ROOT}/internal/register_arithmetic_operators.h"
    "${register_MODULE_ROOT}/internal/register_bitwise_operators.h"
    "${register_MODULE_ROOT}/internal/register_comparison_operators.h")

add_library(register OBJECT ${cpp_sources} ${c_sources})

target_sources(
  register
  PUBLIC FILE_SET
         HEADERS
         TYPE
         HEADERS
         BASE_DIRS
         ${MODULE_ROOT}
         FILES
         ${register_module}
         ${register_internal_register_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

target_link_libraries(register types utility)

# Cant prepend cpu to folder path as it's name is already in use (for a library)
set_target_properties(register PROPERTIES FOLDER "${ROOT_FOLDER_NAME}/libs")

if(MSVC)
  target_compile_definitions(register PRIVATE TANUKIGB_BUILD_DLL)
endif()
