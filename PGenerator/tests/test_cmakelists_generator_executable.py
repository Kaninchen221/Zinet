from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pg.cmakelists_generator_executable import CMakeListsGeneratorExecutable
from pg.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCMakeListsGeneratorExecutable():
    
    def test_inherited_from_CMakelistsGeneratorTarget(self):
        assert issubclass(CMakeListsGeneratorExecutable, CMakeListsGeneratorTarget)

    def test_properties(self):
        expectedTemplatePath = Path(".").absolute() / "pg/templates/CMakeListsExecutableTemplate.txt"
        assert self.generatorExecutable.templatePath == expectedTemplatePath
        assert self.generatorExecutable.templatePath.exists()

    def test_generate_cmake(self):
        templatePath = Path(".").absolute() / "pg/templates/CMakeListsExecutableTemplate.txt"
        
        # Fake file path
        fileLocation = Path(".").absolute() / "tests/test_files/expected_executable_cmakelists.txt"
        self.generatorExecutable.fileLocation = fileLocation
        arguments = self.generatorExecutable.prepare_arguments()

        cmakelists = self.generatorExecutable.generate_cmakelists(arguments)
        expectedCMakeLists = open(Path(".").absolute() / "tests/test_files/expected_executable_cmakelists.txt").read()
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

    generatorExecutable = CMakeListsGeneratorExecutable()