from zinet_pgenerator.cmakelists_generator_target import CMakeListsGeneratorTarget
from zinet_pgenerator.cmakelists_generator_library import CMakeListsGeneratorLibrary
from zinet_pgenerator.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCMakeListsGeneratorLibrary():
    
    def test_inherited_from_CMakelistsGeneratorTarget(self):
        assert issubclass(CMakeListsGeneratorLibrary, CMakeListsGeneratorTarget)

    def test_properties(self):
        assert self.generatorLibrary.libraryType == "STATIC"
        assert self.generatorLibrary.shouldAddTests == "TRUE"
        assert self.generatorLibrary.testsSubfoldersPrefix == "tests_"
        expectedTemplatePath = Path(".").absolute() / "zinet_pgenerator/templates/CMakeListsLibraryTemplate.txt"
        assert self.generatorLibrary.templatePath == expectedTemplatePath
        assert self.generatorLibrary.templatePath.exists()

    def test_prepare_arguments(self):
        testFilesPath = Path(".").absolute() / "tests/test_files/expected_library_cmakelists.txt"
        assert testFilesPath.exists()
        self.generatorLibrary.fileLocation = testFilesPath

        expectedTestsSubfoldersArgument = "add_subdirectory(tests_system)\n\tadd_subdirectory(tests_unit)\n\t"

        arguments = self.generatorLibrary.prepare_arguments()
        assert type(arguments) is SafeDict
        assert arguments['argument_library_type'] == self.generatorLibrary.libraryType
        assert arguments['argument_should_add_tests'] == self.generatorLibrary.shouldAddTests
        assert arguments['argument_tests_subfolders'] == expectedTestsSubfoldersArgument

    def test_generate_cmake(self):
        fileLocation = Path(".").absolute() / "tests/test_files/expected_library_cmakelists.txt"
        assert fileLocation.exists()
        self.generatorLibrary.fileLocation = fileLocation
        arguments = self.generatorLibrary.prepare_arguments()

        cmakelists = self.generatorLibrary.generate_cmakelists(arguments)
        expectedCMakeLists = open(Path(".").absolute() / "tests/test_files/expected_library_cmakelists.txt").read()
        expectedCMakeLists = expectedCMakeLists.format_map(SafeDict(argument_absolute_path=Path(".").absolute()))
        expectedCMakeLists = expectedCMakeLists.replace("\\\\", "/")
        expectedCMakeLists = expectedCMakeLists.replace("\\", "/")

        position = 0
        for (actual, expected) in zip(cmakelists, expectedCMakeLists):
            if (actual != expected):
                previousActual = cmakelists[position - 1]
                previousExpected = expectedCMakeLists[position - 1]
                print(f"Not equal at: {position} {previousActual} {previousExpected}")
                assert False
            position += 1

    generatorLibrary = CMakeListsGeneratorLibrary()