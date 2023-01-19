from pg.project_generator import ProjectGenerator
from pathlib import Path
import numpy

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

    def test_generate_project(self):
        projectRootPath = Path(__file__).parent / 'test_files/fake_project'
        self.projectGenerator.generate_project(projectRootPath)
        assert self.projectGenerator.get_collected_recipes().size == 6
        assert self.projectGenerator.get_generators().size == 6
        
        generatedCMakelists = ProjectGenerator.collect_files(projectRootPath, 'CMakeLists.txt')
        assert generatedCMakelists.size == 6

        # TODO
        # How to check the files are correct filed up?
        # 1. Expected files text in another files in the same folder

    projectGenerator = ProjectGenerator()
