from pg import project_generator
from pg import cmakelists_generator
import pathlib

class TestProjectGenerator:
    def test_variables(self):
        assert self.projectGenerator.projectRootTemplate == "PG/pg/Templates/CMakeListsRootTemplate.txt"

    def test_collect_recipes(self):
        path = pathlib.Path(__file__).parent / 'test_files'
        recipes = self.projectGenerator.collect_recipes(path)
        assert recipes.size == 5
        expected_recipes = [
            'recipe_exec.py',
            'recipe_lib.py',
            'recipe_lib_system_tests.py',
            'recipe_lib_unit_tests.py',
            'recipe_root.py'
        ]
        for recipe in recipes:
            assert issubclass(type(recipe), pathlib.Path)
            recipe_file_name = str(recipe.name)
            assert recipe_file_name in expected_recipes

    def test_generate_cmakelists_from_recipe(self):
        path = pathlib.Path(__file__).parent / 'test_files/recipe_root.py'
        self.projectGenerator.generate_cmakelists_from_recipe(path)
        assert len(self.projectGenerator.generators) == 1
        assert type(self.projectGenerator.generators[0]) is cmakelists_generator.CMakeListsGenerator

    projectGenerator = project_generator.ProjectGenerator()
