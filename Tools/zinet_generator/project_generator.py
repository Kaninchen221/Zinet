from zinet_generator.cmakelists_generator import CMakeListsGenerator
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


    def generate_project(self, projectRootPath, cmdArgs):
        self._collectedRecipes = self.collect_recipes(projectRootPath)
        print("Collected recipes: ", self._collectedRecipes.size)

        for recipePath in self._collectedRecipes:
            self.execute_recipe(recipePath)
            if self._generators.size == 0:
                raise RuntimeError('No valid generators in collected recipes')

            generator = self._generators[-1]
            generator.fileLocation = recipePath
            generator.cmdArgs = cmdArgs
            folder = recipePath.parent
            arguments = generator.prepare_arguments()
            cmakelists = generator.generate_cmakelists(arguments)
            cmakelistsPath = folder / "CMakeLists.txt"
            file = open(cmakelistsPath, "w")
            file.write(cmakelists)
            file.close()


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
