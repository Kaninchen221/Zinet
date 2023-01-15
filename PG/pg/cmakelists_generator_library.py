from pg.safe_dict import SafeDict
from pg.cmakelists_generator_target import CMakeListsGeneratorTarget
from pathlib import Path
import numpy

class CMakeListsGeneratorLibrary(CMakeListsGeneratorTarget):

    def prepare_arguments(self):
        testsSubfolders = ""
        for path in Path(self.fileLocation.parent).iterdir():
            if path.is_dir() and path.name.startswith(self.testsSubfoldersPrefix):
                testsSubfolders += "add_subdirectory(" + path.name + ")\n\t"

        result = super().prepare_arguments()
        result |= SafeDict(
            argument_library_type = self.libraryType,
            argument_should_add_tests = self.shouldAddTests,
            argument_tests_subfolders = testsSubfolders
        )
        return result
        
    libraryType = "STATIC"
    shouldAddTests = "TRUE"
    testsSubfoldersPrefix = "test_"
