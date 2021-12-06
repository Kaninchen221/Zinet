from Scripts.GenerateLibTestCMake import *


renderer_lib_test = ZtLibTestCMakeGenerator()
renderer_lib_test.folder_name = "tests"
renderer_lib_test.pretty_name = "Zinet Graphic Layer Test"
renderer_lib_test.name = "ZtGraphicLayerTest"
renderer_lib_test.header_path = "GraphicLayer/tests/include"
renderer_lib_test.inl_path = "GraphicLayer/tests/include"
renderer_lib_test.source_path = "GraphicLayer/tests/source"
renderer_lib_test.include_dirs_list = [
    "${COLONY_INCLUDE_DIRS}",
    "${GLM_INCLUDE_DIRS}",
    "${STB_INCLUDE_DIRS}",
    "${VULKAN_HPP_INCLUDE_DIRS}"
]
renderer_lib_test.link_libraries_list = [
    "spdlog",
    "gtest",
    "gmock",
    "Glad",
    "glfw",
    "ZtGraphicLayer"
]
renderer_lib_test.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
renderer_lib_test.macros_list.extend(root.global_macros)
renderer_lib_test.cmake_output_file_path = "GraphicLayer/tests/CMakeLists.txt"
renderer_lib_test.generate_cmake_from_template()
renderer_lib_test.create_cmake_file()

root.add_target(renderer_lib_test)
