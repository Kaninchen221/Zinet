from Scripts.GenerateLibCMake import *


renderer_lib = ZtLibCMakeGenerator()
renderer_lib.folder_name = "Renderer"
renderer_lib.pretty_name = "Zinet Renderer"
renderer_lib.name = "ZtRenderer"
renderer_lib.header_path = "Renderer/include"
renderer_lib.inl_path = "Renderer/include"
renderer_lib.source_path = "Renderer/source"
renderer_lib.include_dirs_list = [
    "${COLONY_INCLUDE_DIRS}"
]
renderer_lib.link_libraries_list = [
    "ZtCore",
    "spdlog",
    "Glad",
    "glfw",
]
renderer_lib.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
renderer_lib.macros_list.extend(root.global_macros)
renderer_lib.cmake_output_file_path = "Renderer/CMakeLists.txt"
renderer_lib.generate_cmake_from_template()
renderer_lib.create_cmake_file()

root.add_target(renderer_lib)
