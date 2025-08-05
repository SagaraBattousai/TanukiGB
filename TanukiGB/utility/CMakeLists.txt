set(utility_MODULE_ROOT "${MODULE_ROOT}/TanukiGB/utility")

set(header_files 
    "${utility_MODULE_ROOT}/concepts.h"
    "${utility_MODULE_ROOT}/endianness.h"
    "${utility_MODULE_ROOT}/enum_utils.h"
    "${utility_MODULE_ROOT}/enum_flag_utils.h"
    "${utility_MODULE_ROOT}/integral.h"
    "${utility_MODULE_ROOT}/pimpl.h"
    "${utility_MODULE_ROOT}/crtp.h"
    # "${utility_MODULE_ROOT}/property.h"
    )

add_library(utility INTERFACE)

# set_target_properties(utility PROPERTIES CXX_STANDARD 20)
if (MSVC)
  set_source_files_properties(${header_files} PROPERTIES COMPILE_OPTIONS "/std:c++20")
endif()

target_sources(utility PUBLIC
  FILE_SET HEADERS
  TYPE HEADERS
  BASE_DIRS ${MODULE_ROOT}
  FILES
  ${header_files}
  )
