
add_executable(app main.cpp)
#target_compile_options(TanukiGB PRIVATE ${TANUKIGB_COMPILE_OPTIONS})

target_link_libraries(app memory)

if (WIN32)
  copy_dlls_to_target(app)
endif()
