import os
from Scripts.Utility import *
from Scripts.GenerateTargetCMake import *


class ZinetLibCMakeGenerator(ZinetTargetCMakeGenerator):
    lib_type = 'STATIC'

    def generate_cmake_from_template(self):
        self._prepare_template_arguments()

        template_file = open(self.template_input_file, "r")
        template = template_file.read()
        template_file.close()

        template = template.format_map(SafeDict(
            argument_lib_pretty_name=self.pretty_name,
            argument_lib_name=self.name,
            argument_zinet_lib_type=self.lib_type,
            argument_headers=self._headers_cmake_pathlist,
            argument_inl=self._inl_cmake_pathlist,
            argument_source=self._source_cmake_pathlist,
            argument_cpp_standard=self.cpp_standard,
            argument_link_libraries_string=self._link_libraries_string,
            argument_archive_output_directory=self.archive_output_directory,
            argument_library_output_directory=self.library_output_directory,
            argument_runtime_output_directory=self.runtime_output_directory
        ))
        #print(template)

        self._generated_cmake = template
        #print(_generated_cmake)

    def create_cmake_file(self):
        cmake_file = open(self.cmake_output_file_path, 'w')
        cmake_file.write(self._generated_cmake)
        cmake_file.close()

