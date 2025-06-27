
set(ROOT_FOLDER_NAME "TanukiGB")


add_subdirectory(cpu)
add_subdirectory(memory)
add_subdirectory(types)

set_direct_subtargets_folder(${ROOT_FOLDER_NAME})

