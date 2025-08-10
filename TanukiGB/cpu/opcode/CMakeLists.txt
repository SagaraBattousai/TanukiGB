set(opcode_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu/opcode")

set(cpp_sources "")
set(c_sources "")

set(opcode_module
    "${opcode_MODULE_ROOT}/opcode_handler_fwd_decls.h"
    "${opcode_MODULE_ROOT}/opcode_handler.h"
    "${opcode_MODULE_ROOT}/opcode_tags.h"
    #TODO
    "${opcode_MODULE_ROOT}/opcode_type_traits.h"
    )

set(opcode_internal_module
    "${opcode_MODULE_ROOT}/internal/8bit_load.h"
    "${opcode_MODULE_ROOT}/internal/16bit_load.h"
    "${opcode_MODULE_ROOT}/internal/8bit_arithmetic.h"
    "${opcode_MODULE_ROOT}/internal/16bit_arithmetic.h"
    "${opcode_MODULE_ROOT}/internal/rotate_and_shift.h"
    "${opcode_MODULE_ROOT}/internal/jump.h"
    "${opcode_MODULE_ROOT}/internal/single_bit.h"
    )

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
         ${opcode_internal_module}
         "${MODULE_ROOT}/_TanukiGB_config.h")

set_target_properties(opcode PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(opcode types utility)

# Cant prepend cpu to folder path as it's name is already in use (for a library)
set_target_properties(opcode PROPERTIES FOLDER "${ROOT_FOLDER_NAME}/libs")

if(MSVC)
  target_compile_definitions(opcode PRIVATE TANUKIGB_BUILD_DLL)
endif()
