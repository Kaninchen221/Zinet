from PPG.GenerateLibTestCMake import *


renderer_lib_test = ZtLibTestCMakeGenerator()
renderer_lib_test.folder_name = "tests"
renderer_lib_test.pretty_name = "Zinet Graphic Layer Test"
renderer_lib_test.name = "ZtGraphicLayerTest"
renderer_lib_test.header_path = "GraphicLayer/tests/include"
renderer_lib_test.inl_path = "GraphicLayer/tests/include"
renderer_lib_test.source_path = "GraphicLayer/tests/source"
renderer_lib_test.include_dirs_list = [
    "${CONAN_INCLUDE_DIRS_SPDLOG}",
    "${CONAN_INCLUDE_DIRS_PLF_COLONY}",
    "${CONAN_INCLUDE_DIRS_FMT}",
    "${CONAN_INCLUDE_DIRS_GLM}",
    "${CONAN_INCLUDE_DIRS_GLFW}",
    "${CONAN_INCLUDE_DIRS_STB}",
    "${CONAN_INCLUDE_DIRS_GTEST}",
    "${CONAN_INCLUDE_DIRS_SHADERC}",
    "${CONAN_INCLUDE_DIRS_SPIRV-TOOLS}",
    "${CONAN_INCLUDE_DIRS_VULKAN-MEMORY-ALLOCATOR}",
    "${Vulkan_INCLUDE_DIRS}"
]
renderer_lib_test.link_libraries_list = [
    "ZtCore",
    "ZtGraphicLayer",
    "${Vulkan_LIBRARIES}",
    "${CONAN_LIBS_GTEST}",
    "${CONAN_LIBS_SPDLOG}",
    "${CONAN_LIBS_FMT}",
    "${CONAN_LIBS_GLFW}",
    "${CONAN_LIBS_SHADERC}",
    "${CONAN_LIBS_GLSLANG}",
    "${CONAN_LIBS_SPIRV-TOOLS}",
    "${CONAN_LIBS_SPIRV-HEADERS}",
    "${CONAN_LIBS_VULKAN-MEMORY-ALLOCATOR}"
]
renderer_lib_test.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
renderer_lib_test.macros_list.extend(root.global_macros)
renderer_lib_test.cmake_output_file_path = "GraphicLayer/tests/CMakeLists.txt"
renderer_lib_test.generate_cmake_from_template()
renderer_lib_test.create_cmake_file()

root.add_target(renderer_lib_test)
