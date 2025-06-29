cmake_minimum_required(VERSION 3.29)

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
include(PropertyUtils)
include(DocsUtils)

if(MSVC)
  # Wall removed as msvc has some errors that trigger this
  add_compile_options(/permissive- /W4) # /WX) # Wall)
  # set(VS_STARTUP_PROJECT "")
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(TanukiGB_BUILD_DOCS
    ON
    CACHE BOOL "Whether or not to build documentation.")
  set(TanukiGB_BUILD_TESTS
    ON
    CACHE BOOL "Whether or not to build tests.")


set(MODULE_ROOT "${PROJECT_SOURCE_DIR}/include")

add_subdirectory(app)
add_subdirectory(TanukiGB)


if(TanukiGB_BUILD_TESTS)
  # enable_testing() 
  # add_subdirectory(tests)
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

# While we could get all shared/static libs from the main exe its probably
# best to specify separatly. Though maybe we can check what kind of lib?

set(STATIC_LIBRARIES "")
set(SHARED_LIBRARIES "memory" "cpu")
set(HEADER_ONLY_LIBRARIES "types")

# foreach(shared_lib ${SHARED_LIBRARIES})
#   message(STATUS "shared_lib = ${shared_lib}")
#   get_target_property(headers ${shared_lib} HEADER_SET)
#   message(STATUS "header sets = ${headers}") 
# endforeach()

install(TARGETS memory DESTINATION ${CMAKE_INSTALL_BINDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS app DESTINATION ${CMAKE_INSTALL_BINDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS cpu DESTINATION ${CMAKE_INSTALL_BINDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install(TARGETS <Target_Name> RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION
# ${CMAKE_INSTALL_LIBDIR})

# install(TARGETS cactuar FILE_SET public_headers DESTINATION
# ${CMAKE_INSTALL_INCLUDEDIR}) install(IMPORTED_RUNTIME_ARTIFACTS
# OpenSSL::Crypto RUNTIME_DEPENDENCY_SET external_runtime_deps RUNTIME)

# if(BUILD_DOCS) #Use trailing slashes to avoid adding subdirectories
# install(DIRECTORY "${CMAKE_SOURCE_DIR}/docs/build/sphinx/" DESTINATION
# ${CMAKE_INSTALL_DOCDIR})

# install(DIRECTORY "${CMAKE_SOURCE_DIR}/docs/build/man/" DESTINATION
# ${CMAKE_INSTALL_MANDIR}) endif()
