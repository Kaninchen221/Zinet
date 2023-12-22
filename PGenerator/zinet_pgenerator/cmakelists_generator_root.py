from zinet_pgenerator.cmakelists_generator import CMakeListsGenerator
from zinet_pgenerator.safe_dict import SafeDict
from pathlib import Path

class CMakelistsGeneratorRoot(CMakeListsGenerator):

    def __init__(self) -> None:
        super().__init__()
        self.templatePath = Path(".").absolute() / "zinet_pgenerator/templates/CMakeListsRootTemplate.txt"

    def prepare_arguments(self):
        subdirectories = CMakelistsGeneratorRoot.create_argument_subdirectories(self.subdirectories)
        arguments = SafeDict(
            argument_cmake_minimum_version = self.cmakeMinimumVersion,
            argument_project_name = self.projectName,
            argument_project_version = self.projectVersion,
            argument_project_description = self.projectDescription,
            argument_global_compile_options = self.globalCompileOptions,
            argument_global_compile_definitions = self.globalCompileDefinitions,
            argument_subdirectories = subdirectories
            )
        
        if hasattr(self.cmdArgs, 'AddressSanitizer') and self.cmdArgs.AddressSanitizer == "true":
            arguments["argument_global_compile_options"] += " " + self.globalCompileOptionsForAddressSanitizer

        return arguments

    def create_argument_subdirectories(subdirectories):
        argument = ""
        for subdirectory in subdirectories:
            argument += "add_subdirectory(" + subdirectory + ")\n"
        return argument

    cmakeMinimumVersion = ''
    projectName = ''
    projectVersion = ''
    projectDescription = ''
    globalCompileOptions = ''
    globalCompileOptionsForAddressSanitizer = ''
    globalCompileDefinitions = ''
    subdirectories = ''