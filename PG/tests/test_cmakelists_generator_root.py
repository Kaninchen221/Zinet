from pg import cmakelists_generator_root as cgr
from pg.cmakelists_generator_root import CMakelistsGeneratorRoot
from pg.cmakelists_generator import CMakeListsGenerator
from pg.safe_dict import SafeDict
import pathlib

class TestCmakelistsGeneratorRoot:
    def test_inherited_from_CMakelistsGenerator(self):
        assert issubclass(CMakelistsGeneratorRoot, CMakeListsGenerator)

    def test_prepare_arguments(self):
        self.prepare_arguments()
        arguments = self.generatorRoot.prepare_arguments()
        
        assert type(arguments) is SafeDict
        assert arguments['argument_cmake_minimum_version'] == self.generatorRoot.cmakeMinimumVersion
        assert arguments['argument_project_name'] == self.generatorRoot.projectName
        assert arguments['argument_project_version'] == self.generatorRoot.projectVersion
        assert arguments['argument_project_description'] == self.generatorRoot.projectDescription
        assert arguments['argument_global_compile_options'] == self.generatorRoot.globalCompileOptions
        assert arguments['argument_subdirectories'] == "add_subdirectory(Core)\nadd_subdirectory(GraphicLayer)\n"

    def test_generate_cmakelists(self):
        self.prepare_arguments()
        templatePath = pathlib.Path(".").absolute() / "pg/templates/CMakeListsRootTemplate.txt"
        arguments = self.generatorRoot.prepare_arguments()
        cmakelists = self.generatorRoot.generate_cmakelists(templatePath, arguments)
        expectedCmakelistsPath = pathlib.Path(".").absolute() / "tests/test_files/expected_root.txt"
        expectedCmakelists = open(expectedCmakelistsPath).read()
        assert cmakelists == expectedCmakelists

    def prepare_arguments(self):
        self.generatorRoot.cmakeMinimumVersion = "1.0.0"
        self.generatorRoot.projectName = "project name"
        self.generatorRoot.projectVersion = "project version"
        self.generatorRoot.projectDescription = "description"
        self.generatorRoot.globalCompileOptions = "/W4 /WX"
        self.generatorRoot.subdirectories = ["Core", "GraphicLayer"]


    generatorRoot = CMakelistsGeneratorRoot()