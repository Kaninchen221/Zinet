import os
from Scripts.Utility import *
from Scripts.GeneratorCMake import *
from pathlib import Path


class ZtRootCMakeGenerator(ZtGeneratorCMake):

    _target_recipe_file_name = "target_recipe.py"

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


    def run_all_targets_recipes(self):
        pathlist = Path("./").rglob(self._target_recipe_file_name)
        for path in pathlist:
            exec(open(path).read(), globals())


