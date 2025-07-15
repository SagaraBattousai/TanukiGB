
set(graphics_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/graphics")

set(cpp_sources 
  "ppu.cpp" 
  )

set(c_sources "")
set(graphics_module
  "${graphics_MODULE_ROOT}/ppu.h"
  )

add_library(graphics SHARED ${cpp_sources} ${c_sources})

target_sources(graphics PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES ${graphics_module}
  "${MODULE_ROOT}/_TanukiGB_config.h"
  )

target_link_libraries(graphics types)

if (MSVC)
  target_compile_definitions(graphics PRIVATE TANUKIGB_BUILD_DLL)
endif()
