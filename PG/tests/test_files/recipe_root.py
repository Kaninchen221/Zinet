from pg import project_generator
from pg import cmakelists_generator

generator = cmakelists_generator.CMakeListsGenerator()
projectGenerator.generators.append(generator)
