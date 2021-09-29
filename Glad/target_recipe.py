from Scripts.GenerateLibCMake import *
from Scripts.GenerateRootCMake import *

glad_lib = ZtLibCMakeGenerator()
glad_lib.folder_name = "Glad"
glad_lib.pretty_name = "Glad library"
glad_lib.name = "Glad"

if root.build_type == ZtBuildType.Debug:
    glad_lib.header_path = "Glad/Debug/include"
    glad_lib.inl_path = "Glad/Debug/include"
    glad_lib.source_path = "Glad/Debug/src"
    glad_lib.include_directories = "Debug/include"
elif root.build_type == ZtBuildType.Release:
    glad_lib.header_path = "Glad/Release/include"
    glad_lib.inl_path = "Glad/Release/include"
    glad_lib.source_path = "Glad/Release/src"
    glad_lib.include_directories = "Release/include"

glad_lib.source_extension = "c"  # Glad is C style
glad_lib.include_dirs_list = [
    "${SFML_INCLUDE_DIRS}",
    "${COLONY_INCLUDE_DIRS}"
]
glad_lib.link_libraries_list = [
    "spdlog"
]
glad_lib.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
glad_lib.should_add_test = "FALSE"
glad_lib.macros_list.extend(root.global_macros)
glad_lib.cmake_output_file_path = "Glad/CMakeLists.txt"
glad_lib.generate_cmake_from_template()
glad_lib.create_cmake_file()

root.add_target(glad_lib)
