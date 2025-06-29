
set(memory_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/memory")

set(cpp_sources "memory.cpp" "bootrom.cpp")
set(c_sources "")
set(memory_module 
  "${memory_MODULE_ROOT}/bootrom.h"
  "${memory_MODULE_ROOT}/memory.h" # Cant be internal
  )

add_library(memory SHARED ${cpp_sources} ${c_sources} "${PROJECT_SOURCE_DIR}/bootRoms/dmg.bootrom")

target_sources(memory PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${memory_module}
  "${MODULE_ROOT}/_TanukiGB_config.h"
  )

target_link_libraries(memory types)

if (MSVC)
  target_compile_definitions(memory PRIVATE TANUKIGB_BUILD_DLL)
endif()



# message(STATUS "$<INSTALL_INTERFACE:memory>")
# message(STATUS "$<BUILD_INTERFACE:memory>")
# message(STATUS "$<BUILD_LOCAL_INTERFACE:memory>")

get_target_property(MID memory INCLUDE_DIRECTORIES)

message(STATUS "MID = ${MID}")
