from pg.safe_dict import SafeDict
from pathlib import Path
import os 

class CMakeListsGenerator:
    def generate_cmake_implementation(self, templatePath, dictionary):
        template = open(templatePath).read()
        cmakelists = template.format_map(dictionary)
        cmakelists = cmakelists.replace("\\", "/")
        return cmakelists

    def generate_cmakelists(self, dictionary):
        return self.generate_cmake_implementation(self.templatePath, dictionary)

    def prepare_arguments(self):
        return SafeDict()

    fileLocation = Path(__file__)
    templatePath = Path()