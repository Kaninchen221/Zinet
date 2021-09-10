import os
from Scripts.Utility import *
from Scripts.GeneratorCMake import *


class ZtRootCMakeGenerator(ZtGeneratorCMake):

    cmake_minimum_version = ""

    project_name = ""
    project_version = ""
    project_description = ""

    def _prepare_template_arguments(self):
        self.project_description = '"' + self.project_description + '"'


    def generate_cmake_from_template(self):
        self._prepare_template_arguments()

        template_file = open(ZtRootCMakeGenerator.template_input_file, "r")
        template = template_file.read()
        template_file.close()

        template = template.format_map(SafeDict(
            argument_cmake_minimum_version=self.cmake_minimum_version,
            argument_project_name=self.project_name,
            argument_project_version=self.project_version,
            argument_project_description=self.project_description
        ))

        self._generated_cmake = template

