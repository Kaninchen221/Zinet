import os
from Scripts.Utility import *


class ZinetLibTestCMakeGenerator:
    template_input_file = "Scripts/Templates/CMakeListsLibTestTemplate.txt"

    pretty_name = "Zinet Core"
    name = "ZtCore"

    lib_type = 'STATIC'

    header_path = "Core/include"
    header_extension = "h"

    inl_path = "Core/include"
    inl_extension = "inl"

    source_path = "Core/source"
    source_extension = "cpp"

    cpp_standard = "cxx_std_20"

    link_libraries_list = ["sfml-system", "sfml-window", "sfml-audio", "spdlog", "ImGui-SFML::ImGui-SFML"]

    archive_output_directory = "${CMAKE_BINARY_DIR}/archive/"
    library_output_directory = "${CMAKE_BINARY_DIR}/lib/"
    runtime_output_directory = "${CMAKE_BINARY_DIR}/runtime"

    cmake_output_file_path = "CMakeLists.txt"

    def generate_cmake_from_template(self):
        headers_pathlist = get_all_files(self.header_path, self.header_extension)
        headers_cmake_pathlist = list_string_to_cmake_path_list(headers_pathlist)
        # print(headers_cmake_pathlist)

        inl_pathlist = get_all_files(self.inl_path, self.inl_extension)
        inl_cmake_pathlist = list_string_to_cmake_path_list(inl_pathlist)
        # print(headers_cmake_pathlist)

        source_pathlist = get_all_files(self.source_path, self.source_extension)
        source_cmake_pathlist = list_string_to_cmake_path_list(source_pathlist)
        # print(source_cmake_pathlist)

        link_libraries_string = " "
        link_libraries_string = link_libraries_string.join(self.link_libraries_list)

        template_file = open(self.template_input_file, "r")
        template = template_file.read()
        template_file.close()
        # print(template)

        template = template.format_map(SafeDict(
            argument_lib_pretty_name=self.pretty_name,
            argument_lib_name=self.name,
            argument_zinet_lib_type=self.lib_type,
            argument_headers=headers_cmake_pathlist,
            argument_inl=inl_cmake_pathlist,
            argument_source=source_cmake_pathlist,
            argument_cpp_standard=self.cpp_standard,
            argument_link_libraries_string=link_libraries_string,
            argument_archive_output_directory=self.archive_output_directory,
            argument_library_output_directory=self.library_output_directory,
            argument_runtime_output_directory=self.runtime_output_directory
        ))
        # print(template)

        return template

    def write_template_to_file(self, template):
        cmake_file = open(self.cmake_output_file_path, 'w')
        cmake_file.write(template)
        cmake_file.close()
