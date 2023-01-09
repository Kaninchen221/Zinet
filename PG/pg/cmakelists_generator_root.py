from pg.cmakelists_generator import CMakeListsGenerator
from pg.safe_dict import SafeDict

class CMakelistsGeneratorRoot(CMakeListsGenerator):
    def prepare_arguments(self):
        subdirectories = CMakelistsGeneratorRoot.create_argument_subdirectories(self.subdirectories)
        arguments = SafeDict(
            argument_cmake_minimum_version = self.cmakeMinimumVersion,
            argument_project_name = self.projectName,
            argument_project_version = self.projectVersion,
            argument_project_description = self.projectDescription,
            argument_global_compile_options = self.globalCompileOptions,
            argument_subdirectories = subdirectories
            )
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
    subdirectories = ''