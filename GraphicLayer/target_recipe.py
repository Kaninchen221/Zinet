from Scripts.GenerateLibCMake import *


renderer_lib = ZtLibCMakeGenerator()
renderer_lib.folder_name = "GraphicLayer"
renderer_lib.pretty_name = "Zinet Graphic Layer"
renderer_lib.name = "ZtGraphicLayer"
renderer_lib.header_path = "GraphicLayer/include"
renderer_lib.inl_path = "GraphicLayer/include"
renderer_lib.source_path = "GraphicLayer/source"
renderer_lib.include_dirs_list = [
    "${COLONY_INCLUDE_DIRS}",
    "${GLM_INCLUDE_DIRS}",
    "${STB_INCLUDE_DIRS}",
    "${VULKAN_HPP_INCLUDE_DIRS}",
    "${Vulkan_INCLUDE_DIR}"
]
renderer_lib.link_libraries_list = [
    "ZtCore",
    "spdlog",
    "glfw",
    "${Vulkan_LIBRARIES}"
]
renderer_lib.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
renderer_lib.macros_list.extend(root.global_macros)
renderer_lib.cmake_output_file_path = "GraphicLayer/CMakeLists.txt"
renderer_lib.generate_cmake_from_template()
renderer_lib.create_cmake_file()

root.add_target(renderer_lib)
