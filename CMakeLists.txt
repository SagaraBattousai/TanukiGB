cmake_minimum_required(VERSION 3.31)

project(
  TanukiGB
  VERSION 0.0.1
  DESCRIPTION ""
  LANGUAGES C CXX)

# TODO: Setup as a macro ...
#
# Also note that since this is unlikly to be used as a library ....
#
# Leave C++ standard up to the root application, so set it only if this is the
# current top-level CMake project.
if(CMAKE_SOURCE_DIR STREQUAL TanukiGB_SOURCE_DIR)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED ON)
else()
  if(CMAKE_CXX_STANDARD LESS 20)
    message(
      FATAL_ERROR
        "TanukiGB requires CMAKE_CXX_STANDARD >= 20 (got: ${CMAKE_CXX_STANDARD})")
  endif()
  if(CMAKE_C_STANDARD LESS 11)
    message(
      FATAL_ERROR
        "TanukiGB requires CMAKE_C_STANDARD >= 11 (got: ${CMAKE_C_STANDARD})")
  endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

include(SystemCheck)
include(LibUtils)
include(ResourceUtils)
include(PropertyUtils)
include(DocsUtils)

if(MSVC)
  # Wall removed as msvc has some errors that trigger this
  add_compile_options(/permissive- /W4) # /WX) # Wall)
  # set(VS_STARTUP_PROJECT "")
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(TanukiGB_BUILD_DOCS OFF CACHE BOOL "Whether or not to build documentation.")

set(TanukiGB_BUILD_TESTS OFF CACHE BOOL "Whether or not to build tests.")

set(MODULE_ROOT "${TanukiGB_SOURCE_DIR}/include")

set(BOOTROMS_SOURCE_DIR "${TanukiGB_SOURCE_DIR}/bootroms")

add_subdirectory(TanukiGB)

if(TanukiGB_BUILD_TESTS)
  enable_testing() 
  add_subdirectory(tests)
endif()

if(TanukiGB_BUILD_DOCS)
  add_subdirectory(docs)
endif()

# if(MSVC) 
  # set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT <Startup_Project>)
# endif()

# ----------------------------------------------
# Install settings
# ----------------------------------------------

include(GNUInstallDirs)

# For now we'll use LINK_LIBRARIES as LINK_INTERFACE_LIBRARIES doesn't include the
# public libraries for some reason, or maybe it's obvious.

set(APPLICATION_TARGET "tanukigb_exe")
get_target_property(APPLICATION_LIBRARIES ${APPLICATION_TARGET} LINK_LIBRARIES)

install(TARGETS ${APPLICATION_TARGET} DESTINATION ${CMAKE_INSTALL_BINDIR})

foreach(library ${APPLICATION_LIBRARIES})
  install(TARGETS ${library}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endforeach()

#install(IMPORTED_RUNTIME_ARTIFACTS OpenSSL::Crypto 
# RUNTIME_DEPENDENCY_SET external_runtime_deps RUNTIME)

if(BUILD_DOCS) #Use trailing slashes to avoid adding subdirectories
  install(DIRECTORY "${TanukiGB_SOURCE_DIR}/docs/docs_build/sphinx/"
    DESTINATION ${CMAKE_INSTALL_DOCDIR})

  install(DIRECTORY "${TanukiGB_SOURCE_DIR}/docs/docs_build/man/"
    DESTINATION ${CMAKE_INSTALL_MANDIR})
endif()
