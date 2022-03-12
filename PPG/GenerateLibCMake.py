import os
from PPG.Utility import *
from PPG.GenerateTargetCMake import *


class ZtLibCMakeGenerator(ZtTargetCMakeGenerator):
    lib_type = 'STATIC'

    should_add_test = "TRUE"
    test_subfolder = "tests"

    include_directories = "include/"

    main_header = "ZtCore.h"

    def generate_cmake_from_template(self):
        self._prepare_template_arguments()

        template_file = open(ZtLibCMakeGenerator.template_input_file, "r")
        template = template_file.read()
        template_file.close()

        template = template.format_map(SafeDict(
            argument_pretty_name=self.pretty_name,
            argument_name=self.name,
            argument_lib_type=self.lib_type,
            argument_headers=self._headers_cmake_pathlist,
            argument_inl=self._inl_cmake_pathlist,
            argument_source=self._source_cmake_pathlist,
            argument_cpp_standard=ZtTargetCMakeGenerator.cpp_standard,
            argument_include_dirs=self._include_dirs_string,
            argument_should_add_test=self.should_add_test,
            argument_test_subfolder=ZtLibCMakeGenerator.test_subfolder,
            argument_include_directories=self.include_directories,
            argument_link_libraries_string=self._link_libraries_string,
            argument_macros=self._macros_string,
            argument_archive_output_directory=self.archive_output_directory,
            argument_library_output_directory=self.library_output_directory,
            argument_runtime_output_directory=self.runtime_output_directory
        ))

        self._generated_cmake = template
