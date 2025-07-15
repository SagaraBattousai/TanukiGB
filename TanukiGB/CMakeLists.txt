# Keeping modules as shared libraries because if multiple instances
#   of the app are running. However, I feel we should change the structure/layout
#   somewhat. I'm not used to making applications over libraries.

set(ROOT_FOLDER_NAME "TanukiGB")

add_subdirectory(cpu)
add_subdirectory(graphics)
add_subdirectory(memory)
add_subdirectory(types)
add_subdirectory(utility)

set_direct_subtargets_folder("${ROOT_FOLDER_NAME}/libs")

add_executable(tanukigb_exe tanukigb.cpp)

target_link_libraries(tanukigb_exe cpu memory) #graphics memory)

set_target_properties(tanukigb_exe PROPERTIES FOLDER ${ROOT_FOLDER_NAME})

if (WIN32)
  copy_dlls_to_target(tanukigb_exe)
endif()

