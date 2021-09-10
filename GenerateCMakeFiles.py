from Scripts.GenerateLibCMake import *
from Scripts.GenerateLibTestCMake import *
from Scripts.GenerateRootCMake import *

ZtRootCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsRootTemplate.txt"
root = ZtRootCMakeGenerator()
root.cmake_minimum_version = "3.14"
root.project_name = "Zinet"
root.project_version = "0.1.2"
root.project_description = "Game Engine"
root.cmake_output_file_path = "CMakeLists.txt"
root.generate_cmake_from_template()
root.create_cmake_file()

ZtLibCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsLibTemplate.txt"
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

ZtLibTestCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsLibTestTemplate.txt"
core_lib_test = ZtLibTestCMakeGenerator()
core_lib_test.pretty_name = "Zinet Core Test"
core_lib_test.name = "ZtCoreTest"
core_lib_test.header_path = "Core/tests/include"
core_lib_test.inl_path = "Core/tests/include"
core_lib_test.source_path = "Core/tests/source"
core_lib_test.include_dirs_list = [
    "${COLONY_INCLUDE_DIRS}"
]
core_lib_test.link_libraries_list = [
    "gtest",
    "gmock",
    "ZtCore",
    "sfml-system",
    "sfml-window",
    "sfml-audio",
    "spdlog"
]
core_lib_test.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
core_lib_test.cmake_output_file_path = "Core/tests/CMakeLists.txt"
core_lib_test.generate_cmake_from_template()
core_lib_test.create_cmake_file()
