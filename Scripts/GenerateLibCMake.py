import os
from Scripts.Utility import *
from Scripts.GenerateTargetCMake import *


class ZtLibCMakeGenerator(ZtTargetCMakeGenerator):
    lib_type = 'STATIC'

    test_subfolder = "tests"

    def generate_cmake_from_template(self):
        self._prepare_template_arguments()

        template_file = open(ZtLibCMakeGenerator.template_input_file, "r")
        template = template_file.read()
        template_file.close()

        template = template.format_map(SafeDict(
            argument_pretty_name=self.pretty_name,
            argument_name=self.name,
            argument_zinet_lib_type=ZtLibCMakeGenerator.lib_type,
            argument_headers=self._headers_cmake_pathlist,
            argument_inl=self._inl_cmake_pathlist,
            argument_source=self._source_cmake_pathlist,
            argument_cpp_standard=ZtTargetCMakeGenerator.cpp_standard,
            argument_include_dirs=self._include_dirs_string,
            argument_test_subfolder=ZtLibCMakeGenerator.test_subfolder,
            argument_link_libraries_string=self._link_libraries_string,
            argument_macros=self._macros_string,
            argument_archive_output_directory=self.archive_output_directory,
            argument_library_output_directory=self.library_output_directory,
            argument_runtime_output_directory=self.runtime_output_directory
        ))

        self._generated_cmake = template

