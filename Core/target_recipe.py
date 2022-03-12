from PPG.GenerateLibCMake import *


core_lib = ZtLibCMakeGenerator()
core_lib.folder_name = "Core"
core_lib.pretty_name = "Zinet Core"
core_lib.name = "ZtCore"
core_lib.header_path = "Core/include"
core_lib.inl_path = "Core/include"
core_lib.source_path = "Core/source"
core_lib.include_dirs_list = [
    "${CONAN_INCLUDE_DIRS_SPDLOG}",
    "${CONAN_INCLUDE_DIRS_PLF_COLONY}",
    "${CONAN_INCLUDE_DIRS_FMT}"
]
core_lib.link_libraries_list = [
]
core_lib.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
core_lib.macros_list.extend(root.global_macros)
core_lib.namespace = "zt::gl"
core_lib.cmake_output_file_path = "Core/CMakeLists.txt"
core_lib.generate_cmake_from_template()
core_lib.create_cmake_file()

root.add_target(core_lib)
