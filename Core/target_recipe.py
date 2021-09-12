from Scripts.GenerateLibCMake import *


core_lib = ZtLibCMakeGenerator()
core_lib.pretty_name = "Zinet Core"
core_lib.name = "ZtCore"
core_lib.header_path = "Core/include"
core_lib.inl_path = "Core/include"
core_lib.source_path = "Core/source"
core_lib.include_dirs_list = [
    "${SFML_INCLUDE_DIRS}",
    "${COLONY_INCLUDE_DIRS}"
]
core_lib.link_libraries_list = [
    "sfml-system",
    "sfml-window",
    "sfml-audio",
    "spdlog",
    "ImGui-SFML::ImGui-SFML"
]
core_lib.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
core_lib.cmake_output_file_path = "Core/CMakeLists.txt"
core_lib.generate_cmake_from_template()
core_lib.create_cmake_file()