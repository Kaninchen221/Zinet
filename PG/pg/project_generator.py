import pathlib
from array import array
import numpy

class ProjectGenerator:
    def collect_recipes(self, path):
        print("Find recipes in path: " + str(path))
        paths = path.rglob('recipe_*.py')
        return numpy.fromiter(paths, pathlib.Path)

    def generate_cmakelists_from_recipe(self, path):
        args = {
            "projectGenerator": self
        }
        print("Exec recipt: " + str(path))
        exec(open(path).read(), args)

    projectRootTemplate = "PG/pg/Templates/CMakeListsRootTemplate.txt"
    generators = []
