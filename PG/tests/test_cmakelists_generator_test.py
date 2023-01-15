from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pg.cmakelists_generator_test import CMakeListsGeneratorTest
from pg.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCMakeListsGeneratorTest():
    
    def test_inherited_from_CMakelistsGeneratorTarget(self):
        assert issubclass(CMakeListsGeneratorTest, CMakeListsGeneratorTarget)

    def test_properties(self):
        #assert self.generatorTarget.targetName == "target_name"
        pass

    def test_generate_cmake(self):
        templatePath = Path(".").absolute() / "pg/templates/CMakeListsTestTemplate.txt"
        
        # Fake file path
        fileLocation = Path(".").absolute() / "tests/test_files/expected_test_cmakelists.txt"
        self.generatorTest.fileLocation = fileLocation
        arguments = self.generatorTest.prepare_arguments()

        cmakelists = self.generatorTest.generate_cmakelists(templatePath, arguments)
        expectedCMakeLists = open(Path(".").absolute() / "tests/test_files/expected_test_cmakelists.txt").read()
        expectedCMakeLists = expectedCMakeLists.replace("\\\\", "/")

        position = 0
        for (actual, expected) in zip(cmakelists, expectedCMakeLists):
            if (actual != expected):
                previousActual = cmakelists[position - 1]
                previousExpected = expectedCMakeLists[position - 1]
                print(f"Not equal at: {position} {previousActual} {previousExpected}")
                assert False
            position += 1

    generatorTest = CMakeListsGeneratorTest()