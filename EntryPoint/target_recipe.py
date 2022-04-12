from PPG.GenerateEntryPointCMake import *


EntryPoint = ZtEntryPointCMakeGenerator()
EntryPoint.folder_name = "EntryPoint"
EntryPoint.pretty_name = "Entry Point"
EntryPoint.name = "ZtEntryPoint"
EntryPoint.header_path = "EntryPoint/include"
EntryPoint.inl_path = "EntryPoint/include"
EntryPoint.source_path = "EntryPoint/source"
EntryPoint.include_dirs_list = [
    "${SFML_INCLUDE_DIRS}",
    "${COLONY_INCLUDE_DIRS}",
    "${GLM_INCLUDE_DIRS}",
    "${STB_INCLUDE_DIRS}",
    "${VULKAN_HPP_INCLUDE_DIRS}"
]
EntryPoint.link_libraries_list = [
    "ZtCore",
    "${Vulkan_LIBRARIES}",
    "${Vulkan_LIBRARIES}",
    "${CONAN_LIBS_GTEST}",
    "${CONAN_LIBS_SPDLOG}",
    "${CONAN_LIBS_FMT}",
    "${CONAN_LIBS_GLFW}",
    "${CONAN_LIBS_SHADERC}",
    "${CONAN_LIBS_GLSLANG}",
    "${CONAN_LIBS_SPIRV-TOOLS}",
    "${CONAN_LIBS_SPIRV-HEADERS}"
    "ZtGraphicLayer"
]
EntryPoint.macros_list = [
    "${CMAKE_CURRENT_SOURCE_DIR}"
]
EntryPoint.macros_list.extend(root.global_macros)
EntryPoint.cmake_output_file_path = "EntryPoint/CMakeLists.txt"
EntryPoint.generate_cmake_from_template()
EntryPoint.create_cmake_file()

root.add_target(EntryPoint)
