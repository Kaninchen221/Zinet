from pg.cmakelists_generator import CMakeListsGenerator
from pg.safe_dict import SafeDict
import pathlib

class TestCmakelistsGenerator:
    def test_generate_cmake(self):
        templatePath = pathlib.Path(".").absolute() / "tests/test_files/template_simple.txt"
        arguments = SafeDict(arg1 = "1", arg2 = "2", arg3 = "3")
        cmakelists = self.cmakelistsGenerator.generate_cmakelists(templatePath, arguments)
        assert isinstance(cmakelists, str)
        assert cmakelists == "1 3 2"

    def test_prepare_arguments(self):
        arguments = self.cmakelistsGenerator.prepare_arguments()
        assert type(arguments) is SafeDict

    cmakelistsGenerator = CMakeListsGenerator()
