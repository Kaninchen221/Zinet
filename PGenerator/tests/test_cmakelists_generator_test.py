from zinet_pgenerator.cmakelists_generator_target import CMakeListsGeneratorTarget
from zinet_pgenerator.cmakelists_generator_test import CMakeListsGeneratorTest
from zinet_pgenerator.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCMakeListsGeneratorTest():
    
    def test_inherited_from_CMakelistsGeneratorTarget(self):
        assert issubclass(CMakeListsGeneratorTest, CMakeListsGeneratorTarget)

    def test_properties(self):
        expectedTemplatePath = Path(".").absolute() / "zinet_pgenerator/templates/CMakeListsTestTemplate.txt"
        assert self.generatorTest.templatePath == expectedTemplatePath
        assert self.generatorTest.templatePath.exists()

    def test_generate_cmake(self):
        templatePath = Path(".").absolute() / "zinet_pgenerator/templates/CMakeListsTestTemplate.txt"
        
        # Fake file path
        fileLocation = Path(".").absolute() / "tests/test_files/expected_test_cmakelists.txt"
        self.generatorTest.fileLocation = fileLocation
        arguments = self.generatorTest.prepare_arguments()

        cmakelists = self.generatorTest.generate_cmakelists(arguments)
        expectedCMakeLists = open(Path(".").absolute() / "tests/test_files/expected_test_cmakelists.txt").read()
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

    generatorTest = CMakeListsGeneratorTest()