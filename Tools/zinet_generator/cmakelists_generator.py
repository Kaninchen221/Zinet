from zinet_generator.safe_dict import SafeDict
from pathlib import Path


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

    @staticmethod
    def get_templates_folder():
        path = (Path(".") / "templates").absolute()
        if not path.exists():
            for parent_path in path.parents:
                templates_path = parent_path / "zinet_generator/templates"
                if templates_path.exists():
                    return templates_path

            raise Exception(f"Can't return valid templates folder \n{path}")

    fileLocation = Path(__file__)
    templatePath = Path()
    cmdArgs = ''
