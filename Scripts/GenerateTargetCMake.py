import os
from Scripts.Utility import *


class ZinetTargetCMakeGenerator:
    template_input_file = "Scripts/Templates/CMakeListsLibTemplate.txt"

    pretty_name = ""
    name = ""

    header_path = ""
    header_extension = "h"

    inl_path = ""
    inl_extension = "inl"

    source_path = ""
    source_extension = "cpp"

    cpp_standard = "cxx_std_20"

    link_libraries_list = []

    archive_output_directory = "${CMAKE_BINARY_DIR}/archive/"
    library_output_directory = "${CMAKE_BINARY_DIR}/lib/"
    runtime_output_directory = "${CMAKE_BINARY_DIR}/runtime"

    cmake_output_file_path = "CMakeLists.txt"

    _headers_cmake_pathlist = ""
    _inl_cmake_pathlist = ""
    _source_cmake_pathlist = ""
    _link_libraries_string = ""

    _generated_cmake = ""

    def generate_cmake_from_template(self):
        _prepare_template_arguments()

        template = template.format_map(SafeDict(
            argument_lib_pretty_name=self.pretty_name,
            argument_lib_name=self.name,
            argument_headers=headers_cmake_pathlist,
            argument_inl=inl_cmake_pathlist,
            argument_source=source_cmake_pathlist,
            argument_cpp_standard=self.cpp_standard,
            argument_link_libraries_string=_link_libraries_string,
            argument_archive_output_directory=self.archive_output_directory,
            argument_library_output_directory=self.library_output_directory,
            argument_runtime_output_directory=self.runtime_output_directory
        ))
        # print(template)

        _generated_cmake = template

    def _prepare_template_arguments(self):
        headers_pathlist = get_all_files(self.header_path, self.header_extension)
        self._headers_cmake_pathlist = list_string_to_cmake_path_list(headers_pathlist)
        # print(headers_cmake_pathlist)

        inl_pathlist = get_all_files(self.inl_path, self.inl_extension)
        self._inl_cmake_pathlist = list_string_to_cmake_path_list(inl_pathlist)
        # print(headers_cmake_pathlist)

        source_pathlist = get_all_files(self.source_path, self.source_extension)
        self._source_cmake_pathlist = list_string_to_cmake_path_list(source_pathlist)
        # print(source_cmake_pathlist)

        self._link_libraries_string = " "
        self._link_libraries_string = self._link_libraries_string.join(self.link_libraries_list)

    def create_cmake_file(self):
        cmake_file = open(self.cmake_output_file_path, 'w')
        cmake_file.write(self._generated_cmake)
        cmake_file.close()

