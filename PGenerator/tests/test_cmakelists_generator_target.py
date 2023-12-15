from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pg.cmakelists_generator import CMakeListsGenerator
from pg.safe_dict import SafeDict
from pathlib import Path
import pytest

class TestCmakelistsGeneratorTarget:
    def test_inherited_from_CMakelistsGenerator(self):
        assert issubclass(CMakeListsGeneratorTarget, CMakeListsGenerator)

    def test_properties(self):
        assert self.generatorTarget.targetName == "target_name"
        assert self.generatorTarget.targetPrettyName == "target_pretty_name"
        assert self.generatorTarget.headersExtension == "h"
        assert self.generatorTarget.headersSubfolder == "include"
        assert self.generatorTarget.sourcesExtension == "cpp"
        assert self.generatorTarget.sourcesSubfolder == "source"
        assert self.generatorTarget.cppVersion == "cxx_std_20"
        assert self.generatorTarget.includeDirectories == ""
        assert self.generatorTarget.linkLibraries == ""
        assert self.generatorTarget.compileDefinitions == ""
        assert self.generatorTarget.archiveOutputSubfolder == "archive"
        assert self.generatorTarget.libraryOutputSubfolder == "lib"
        assert self.generatorTarget.runtimeOutputSubfolder == "runtime"

    def test_prepare_arguments(self):
        self.generatorTarget.includeDirectories = "includeDirectories"
        self.generatorTarget.linkLibraries = "linkLibraries"
        self.generatorTarget.compileDefinitions = "compileDefinitions"

        testFilesPath = Path(".").absolute() / "tests/test_files"
        paths = [testFilesPath / self.generatorTarget.headersSubfolder]
        extensions = [self.generatorTarget.headersExtension]
        headersSubfolder = self.generatorTarget.headersSubfolder
        sourcesSubfolder = self.generatorTarget.sourcesSubfolder
        expectedFilesArgument = "\"" + str(testFilesPath / headersSubfolder / "header1.h\"") + "\n\t\"" + str(testFilesPath / headersSubfolder / "header2.h") + "\"\n\t\n\t"
        expectedFilesArgument += "\"" + str(testFilesPath / sourcesSubfolder / "source1.cpp\"") + "\n\t\"" + str(testFilesPath / sourcesSubfolder / "source2.cpp") + "\"\n\t\n\t"

        self.generatorTarget.fileLocation = testFilesPath / "test_files"

        arguments = self.generatorTarget.prepare_arguments()
        assert self.generatorTarget.files == expectedFilesArgument
        assert type(arguments) is SafeDict
        assert arguments['argument_target_name'] == self.generatorTarget.targetName
        assert arguments['argument_target_pretty_name'] == self.generatorTarget.targetPrettyName
        assert arguments['argument_headers_subfolder'] == self.generatorTarget.headersSubfolder
        assert arguments['argument_sources_subfolder'] == self.generatorTarget.sourcesSubfolder
        assert arguments['argument_files'] == self.generatorTarget.files
        assert arguments['argument_cpp_version'] == self.generatorTarget.cppVersion
        assert arguments['argument_include_directories'] == self.generatorTarget.includeDirectories
        assert arguments['argument_link_libraries'] == self.generatorTarget.linkLibraries
        assert arguments['argument_compile_definitions'] == self.generatorTarget.compileDefinitions
        assert arguments['argument_archive_output_subfolder'] == self.generatorTarget.archiveOutputSubfolder
        assert arguments['argument_library_output_subfolder'] == self.generatorTarget.libraryOutputSubfolder
        assert arguments['argument_runtime_output_subfolder'] == self.generatorTarget.runtimeOutputSubfolder

    generatorTarget = CMakeListsGeneratorTarget()