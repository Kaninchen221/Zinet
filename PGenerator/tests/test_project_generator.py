from zinet_pgenerator.project_generator import ProjectGenerator
from pathlib import Path
import numpy
import pytest_mock
import argparse

class TestProjectGenerator:
    def test_properties(self):
        assert self.projectGenerator.get_generators().size == 0
        assert self.projectGenerator.get_collected_recipes().size == 0

    def test_collect_recipes(self):
        path = Path(__file__).parent / 'test_files'
        recipes = self.projectGenerator.collect_recipes(path)
        assert recipes.size == 11
        for recipe in recipes:
            assert issubclass(type(recipe), Path)
            recipe_file_name = str(recipe.name)
            assert recipe_file_name.startswith("recipe_")

    def test_execute_recipe(self):
        path = Path(__file__).parent / 'test_files/recipe_root.py'
        self.projectGenerator.execute_recipe(path)

    def test_generate_project(self, mocker):
        projectRootPath = Path(__file__).parent / 'test_files/fake_project'
        
        parser = argparse.ArgumentParser(description='PG')
        parser.add_argument('--AddressSanitizer', type=str, help='true or false', default='false')
        cmdArgs, unknownCmdArgs = parser.parse_known_args()
        
        self.projectGenerator.generate_project(projectRootPath, cmdArgs)
        assert self.projectGenerator.get_collected_recipes().size == 6
        assert self.projectGenerator.get_generators().size == 6
        
        generatedCMakelists = ProjectGenerator.collect_files(projectRootPath, 'CMakeLists.txt')
        assert generatedCMakelists.size == 6
        for generatedCMake in generatedCMakelists:
            file = open(generatedCMake, "r")
            text = file.read()
            assert text != ''
            # TODO Use correct generator in recipes

    projectGenerator = ProjectGenerator()
