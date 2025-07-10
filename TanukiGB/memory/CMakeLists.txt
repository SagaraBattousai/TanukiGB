
set(memory_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/memory")

set(bootrom_headers "gameboy_rom.h" "gameboy_colour_rom.h")
set(cpp_sources "memory.cpp" "bootrom.cpp")
set(c_sources "")
set(memory_module 
  "${memory_MODULE_ROOT}/bootrom.h"
  "${memory_MODULE_ROOT}/memory.h"
  "${memory_MODULE_ROOT}/addressable.h"
  )

add_library(memory SHARED ${cpp_sources} ${c_sources} ${bootrom_headers})

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

set(GAMEBOY_BOOTROM_PATH "${BOOTROMS_SOURCE_DIR}/dmg.bootrom")
set(GAMEBOY_COLOUR_BOOTROM_PATH "${BOOTROMS_SOURCE_DIR}/cgb.bootrom")

# embed_file_as_macro(${GAMEBOY_BOOTROM_PATH}
#   "${CMAKE_CURRENT_SOURCE_DIR}/gameboy_rom_buffer.h")
# set(TEST_STRING "gameboy_rom_buffer.h.ht.c")
# message(STATUS "Reg out = ${RRO}")


# file(READ ${GAMEBOY_BOOTROM_PATH} file_contents HEX)
# file(SIZE ${GAMEBOY_BOOTROM_PATH} file_size)
# string(REGEX MATCHALL "[0-9a-f][0-9a-f]" gb_hex ${file_contents})

# message(STATUS "GB ROM")
# message(STATUS ${file_size})
# message(STATUS ${gb_hex})
# message(STATUS "--")


# file(READ ${GAMEBOY_COLOUR_BOOTROM_PATH} file_contents HEX)
# file(SIZE ${GAMEBOY_COLOUR_BOOTROM_PATH} file_size)
# string(REGEX MATCHALL "[0-9a-f][0-9a-f]" gb_hex ${file_contents})

# message(STATUS "CGB ROM")
# message(STATUS ${file_size})
# message(STATUS ${gb_hex})
# message(STATUS "--")
