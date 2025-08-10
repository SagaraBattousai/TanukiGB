set(cpu_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/cpu")

# set(CPU_ROOT_FOLDER_NAME "${ROOT_FOLDER_NAME}/libs/cpu_libs")

set(cpp_sources "cpu.cpp")

set(c_sources "")
set(cpu_module
    "${cpu_MODULE_ROOT}/cpu.h" 
    # TEMP
    "${cpu_MODULE_ROOT}/register_tags.h"
    "${cpu_MODULE_ROOT}/executor.h"
    "${cpu_MODULE_ROOT}/jump_table.h"
    )
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

add_subdirectory(register)
add_subdirectory(opcode)
target_link_libraries(cpu memory types utility register opcode)

if(MSVC)
  target_compile_definitions(cpu PRIVATE TANUKIGB_BUILD_DLL)
endif()
