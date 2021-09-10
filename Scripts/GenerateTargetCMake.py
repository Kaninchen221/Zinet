import os
from Scripts.Utility import *
from Scripts.GeneratorCMake import *


class ZtTargetCMakeGenerator(ZtGeneratorCMake):

    pretty_name = ""
    name = ""

    header_path = ""
    header_extension = "h"

    inl_path = ""
    inl_extension = "inl"

    source_path = ""
    source_extension = "cpp"

    cpp_standard = "cxx_std_20"

    include_dirs_list = []

    link_libraries_list = []

    macros_list = []

    archive_output_directory = "${CMAKE_BINARY_DIR}/archive/"
    library_output_directory = "${CMAKE_BINARY_DIR}/lib/"
    runtime_output_directory = "${CMAKE_BINARY_DIR}/runtime"

    _headers_cmake_pathlist = ""
    _inl_cmake_pathlist = ""
    _source_cmake_pathlist = ""
    _include_dirs_string = ""
    _link_libraries_string = ""
    _macros_string = ""

    #def generate_cmake_from_template(self):
        #_prepare_template_arguments()
        #_generated_cmake = template

    def _prepare_template_arguments(self):
        headers_pathlist = get_all_files(self.header_path, self.header_extension)
        self._headers_cmake_pathlist = list_string_to_cmake_path_list(headers_pathlist)

        inl_pathlist = get_all_files(self.inl_path, self.inl_extension)
        self._inl_cmake_pathlist = list_string_to_cmake_path_list(inl_pathlist)

        source_pathlist = get_all_files(self.source_path, self.source_extension)
        self._source_cmake_pathlist = list_string_to_cmake_path_list(source_pathlist)

        self._link_libraries_string = " "
        self._link_libraries_string = self._link_libraries_string.join(self.link_libraries_list)

        self._include_dirs_string = " "
        self._include_dirs_string = self._include_dirs_string.join(self.include_dirs_list)

        self._macros_string = " "
        self._macros_string = self._macros_string.join(self.macros_list)

