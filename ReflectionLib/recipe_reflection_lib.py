from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetName = "ZinetReflection"
core.targetPrettyName = "Zinet Reflection"
core.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    """
core.includeDirectories = """
    """
core.linkLibraries = """
    ZinetCore
    """
projectGenerator.add_generator(core)