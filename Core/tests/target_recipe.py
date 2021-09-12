from Scripts.GenerateLibTestCMake import *


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