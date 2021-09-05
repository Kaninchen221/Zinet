from Scripts.GenerateLibCMake import *
from Scripts.GenerateLibTestCMake import *

core_lib_generator = ZinetLibCMakeGenerator()
core_lib_generator.template_input_file = "Scripts/Templates/CMakeListsLibTemplate.txt"
core_lib_generator.pretty_name = "Zinet Core"
core_lib_generator.name = "ZtCore"
core_lib_generator.header_path = "Core/include"
core_lib_generator.inl_path = "Core/include"
core_lib_generator.source_path = "Core/source"
core_lib_generator.cpp_standard = "cxx_std_20"
core_lib_generator.link_libraries_list = [
    "sfml-system",
    "sfml-window",
    "sfml-audio",
    "spdlog",
    "ImGui-SFML::ImGui-SFML"]
core_lib_generator.cmake_output_file_path = "Core/CMakeLists.txt"
core_lib_generator.generate_cmake_from_template()
core_lib_generator.create_cmake_file()


