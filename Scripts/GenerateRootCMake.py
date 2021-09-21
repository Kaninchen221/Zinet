import os
from Scripts.Utility import *
from Scripts.GeneratorCMake import *
from pathlib import Path
from Scripts.GenerateLibCMake import *
from Scripts.GenerateLibTestCMake import *


class ZtRootCMakeGenerator(ZtGeneratorCMake):

    _target_recipe_file_name = "target_recipe.py"

    _targets_libs_list = []
    _targets_libs_tests_list = []

    _subdirectories_list = []
    _add_subdirectory_string = ")\nadd_subdirectory("

    cmake_minimum_version = ""

    project_name = ""
    project_version = ""
    project_description = ""

    global_macros = []

    def _prepare_template_arguments(self):
        self.project_description = '"' + self.project_description + '"'

        for target_lib in self._targets_libs_list:
            self._subdirectories_list.append(target_lib.folder_name)
        self._add_subdirectory_string = self._add_subdirectory_string.join(self._subdirectories_list)
        self._add_subdirectory_string = "add_subdirectory(" + self._add_subdirectory_string + ")"


    def generate_cmake_from_template(self):
        self._prepare_template_arguments()

        template_file = open(ZtRootCMakeGenerator.template_input_file, "r")
        template = template_file.read()
        template_file.close()

        template = template.format_map(SafeDict(
            argument_cmake_minimum_version=self.cmake_minimum_version,
            argument_project_name=self.project_name,
            argument_project_version=self.project_version,
            argument_project_description=self.project_description,
            argument_subdirectories=self._add_subdirectory_string
        ))

        self._generated_cmake = template

    def run_all_targets_recipes(self):
        path_list = Path("./").rglob(self._target_recipe_file_name)
        for path in path_list:
            args = {
                "root": self
            }
            exec(open(path).read(), args)

    def add_target(self, target):
        if isinstance(target, ZtLibCMakeGenerator):
            self._targets_libs_list.append(target)
            print("Added lib target: " + target.pretty_name)
        elif isinstance(target, ZtLibTestCMakeGenerator):
            self._targets_libs_tests_list.append(target)
            print("Added lib test target: " + target.pretty_name)

