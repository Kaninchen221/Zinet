from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary
from pg.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCMakeListsGeneratorLibrary():
    
    def test_inherited_from_CMakelistsGeneratorTarget(self):
        assert issubclass(CMakeListsGeneratorLibrary, CMakeListsGeneratorTarget)

    def test_properties(self):
        assert self.generatorLibrary.libraryType == "STATIC"
        assert self.generatorLibrary.shouldAddTests == "TRUE"
        assert self.generatorLibrary.testsSubfoldersPrefix == "test_"

    def test_prepare_arguments(self):
        testFilesPath = Path(".").absolute() / "tests/test_files"
        self.generatorLibrary.fileLocation = testFilesPath

        expectedTestsSubfoldersArgument = "add_subdirectory(test_system)\nadd_subdirectory(test_unit)\n"

        arguments = self.generatorLibrary.prepare_arguments()
        assert type(arguments) is SafeDict
        assert arguments['argument_library_type'] == self.generatorLibrary.libraryType
        assert arguments['argument_should_add_tests'] == self.generatorLibrary.shouldAddTests
        assert arguments['argument_tests_subfolders'] == expectedTestsSubfoldersArgument

    generatorLibrary = CMakeListsGeneratorLibrary()