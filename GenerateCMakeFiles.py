from Scripts.GenerateEntryPointCMake import *
from Scripts.GenerateLibCMake import *
from Scripts.GenerateLibTestCMake import *
from Scripts.GenerateRootCMake import *


ZtRootCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsRootTemplate.txt"
ZtLibCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsLibTemplate.txt"
ZtLibTestCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsLibTestTemplate.txt"
ZtEntryPointCMakeGenerator.template_input_file = "Scripts/Templates/CMakeListsEntryPointTemplate.txt"

# First prepare all root properties
root = ZtRootCMakeGenerator()
root.cmake_minimum_version = "3.14"
root.project_name = "Zinet"
root.project_version = "0.1.2"
root.project_description = "Game Engine"
root.cmake_output_file_path = "CMakeLists.txt"
root.build_type = ZtBuildType.Debug
root.global_macros.extend([
    "ZINET_WINDOWS",
    "ZINET_CURRENT_PROJECT_ROOT_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\""
])

# Generate all targets CMakeLists and gather all targets
root.run_all_targets_recipes()

# Generate root CMakeLists
root.generate_cmake_from_template()
root.create_cmake_file()
