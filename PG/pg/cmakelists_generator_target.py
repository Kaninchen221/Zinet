from pg.safe_dict import SafeDict
from pg.cmakelists_generator import CMakeListsGenerator
from pathlib import Path
import numpy

class CMakeListsGeneratorTarget(CMakeListsGenerator):

    def __init__(self) -> None:
        super().__init__()

    def create_argument_files(paths, extensions):
        argument = ""
        for path, extension in zip(paths, extensions):
            filesPaths = Path(path).rglob('*.' + extension)
            filesPaths = numpy.fromiter(filesPaths, Path)
            for filePath in filesPaths:
                argument += str(filePath) + "\n"
            argument += "\n"
        return argument

    def prepare_arguments(self):
        pathsToFindFiles = [self.fileLocation.parent / self.headersSubfolder, self.fileLocation.parent / self.sourcesSubfolder]
        extensions = [self.headersExtension, self.sourcesExtension]
        self.files = CMakeListsGeneratorTarget.create_argument_files(pathsToFindFiles, extensions)
        arguments = SafeDict(
            argument_target_name = self.targetName,
            argument_files = self.files,
            argument_cpp_version = self.cppVersion,
            argument_include_directories = self.includeDirectories,
            argument_link_libraries = self.linkLibraries,
            argument_compile_definitions = self.compileDefinitions,
            argument_archive_output_subfolder = self.archiveOutputSubfolder,
            argument_library_output_subfolder = self.libraryOutputSubfolder,
            argument_runtime_output_subfolder = self.runtimeOutputSubfolder
            )
        return arguments
        
    targetName = "target_name"
    files = ""
    headersExtension = "h"
    headersSubfolder = "include"
    sourcesExtension = "cpp"
    sourcesSubfolder = "source"
    includeDirectories = ""
    cppVersion = "cxx_std_20"
    linkLibraries = ""
    compileDefinitions = ""
    archiveOutputSubfolder = "archive"
    libraryOutputSubfolder = "lib"
    runtimeOutputSubfolder = "runtime"

