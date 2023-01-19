from pg.cmakelists_generator import CMakeListsGenerator
from pathlib import Path
from array import array
import numpy

class ProjectGenerator:
    def collect_recipes(self, path):
        print("Find recipes in path: " + str(path))
        paths = ProjectGenerator.collect_files(path, 'recipe_*.py')
        return paths

    def execute_recipe(self, path):
        args = {
            "projectGenerator": self
        }
        print("Exec recipt: " + str(path))
        exec(open(path).read(), args)

    def generate_project(self, projectRootPath):
        self._collectedRecipes = self.collect_recipes(projectRootPath)
        for recipe in self._collectedRecipes:
            self.execute_recipe(recipe)
            recipeFolder = recipe.parent
            cmakelistsPath = recipeFolder / "CMakeLists.txt"
            open(cmakelistsPath, "w")

    def collect_files(path, format):
        paths = path.rglob(format)
        return numpy.fromiter(paths, Path)

    def add_generator(self, generator):
        self._generators = numpy.append(self._generators, generator)

    def get_generators(self):
        return self._generators

    def get_collected_recipes(self):
        return self._collectedRecipes

    _generators = numpy.empty(0, CMakeListsGenerator)
    _collectedRecipes = numpy.empty(0, Path)
