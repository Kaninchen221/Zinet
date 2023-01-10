from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pg.cmakelists_generator import CMakeListsGenerator
from pg.safe_dict import SafeDict
from pathlib import Path

class TestCmakelistsGenerator:
    def test_inherited_from_CMakelistsGenerator(self):
        assert issubclass(CMakeListsGeneratorTarget, CMakeListsGenerator)

    def test_properties(self):
        assert self.generatorTarget.targetName == "target_name"
        assert self.generatorTarget.headersExtension == "h"
        assert self.generatorTarget.headersSubfolder == "include"
        assert self.generatorTarget.sourcesExtension == "cpp"
        assert self.generatorTarget.sourcesSubfolder == "source"
        assert self.generatorTarget.cppVersion == "cxx_std_20"
        assert self.generatorTarget.includeDirectories == ""
        assert self.generatorTarget.linkLibraries == ""
        assert self.generatorTarget.compileDefinitions == ""

    def test_create_argument_files(self):
        testFilesPath = Path(".").absolute() / "tests/test_files"
        paths = [testFilesPath / self.generatorTarget.headersSubfolder]
        paths.append(testFilesPath / self.generatorTarget.sourcesSubfolder)
        extensions = [self.generatorTarget.headersExtension]
        extensions.append(self.generatorTarget.sourcesExtension)

        argument = CMakeListsGeneratorTarget.create_argument_files(paths, extensions)
        headersSubfolder = self.generatorTarget.headersSubfolder
        sourcesSubfolder = self.generatorTarget.sourcesSubfolder
        expectedArgument = str(testFilesPath / headersSubfolder / "header1.h") + "\n" + str(testFilesPath / headersSubfolder / "header2.h") + "\n\n"
        expectedArgument += str(testFilesPath / sourcesSubfolder / "source1.cpp") + "\n" + str(testFilesPath / sourcesSubfolder / "source2.cpp") + "\n\n"
        assert argument == expectedArgument

    def test_prepare_arguments(self):
        self.generatorTarget.includeDirectories = "includeDirectories"
        self.generatorTarget.linkLibraries = "linkLibraries"
        self.generatorTarget.compileDefinitions = "compileDefinitions"

        testFilesPath = Path(".").absolute() / "tests/test_files"
        paths = [testFilesPath / self.generatorTarget.headersSubfolder]
        extensions = [self.generatorTarget.headersExtension]
        headersSubfolder = self.generatorTarget.headersSubfolder
        sourcesSubfolder = self.generatorTarget.sourcesSubfolder
        expectedFilesArgument = str(testFilesPath / headersSubfolder / "header1.h") + "\n" + str(testFilesPath / headersSubfolder / "header2.h") + "\n\n"
        expectedFilesArgument += str(testFilesPath / sourcesSubfolder / "source1.cpp") + "\n" + str(testFilesPath / sourcesSubfolder / "source2.cpp") + "\n\n"

        self.generatorTarget.fileLocation = testFilesPath / "test_files"

        arguments = self.generatorTarget.prepare_arguments()
        assert self.generatorTarget.files == expectedFilesArgument
        assert type(arguments) is SafeDict
        assert arguments['argument_target_name'] == self.generatorTarget.targetName
        assert arguments['argument_files'] == self.generatorTarget.files
        assert arguments['argument_cpp_version'] == self.generatorTarget.cppVersion
        assert arguments['argument_include_directories'] == self.generatorTarget.includeDirectories
        assert arguments['argument_link_libraries'] == self.generatorTarget.linkLibraries
        assert arguments['argument_compile_definitions'] == self.generatorTarget.compileDefinitions

    generatorTarget = CMakeListsGeneratorTarget()