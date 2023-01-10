from pg.safe_dict import SafeDict
from pathlib import Path

class CMakeListsGenerator:
    def generate_cmakelists(self, templatePath, dictionary):
        template = open(templatePath).read()
        cmakelists = template.format_map(dictionary)
        return cmakelists

    def prepare_arguments(self):
        return SafeDict()

    fileLocation = Path(__file__)