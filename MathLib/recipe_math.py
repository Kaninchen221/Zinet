from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetName = "ZinetMath"
core.targetPrettyName = "Zinet Math"
core.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    ZINET_LIB
    """
core.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_GLM}
    """
core.linkLibraries = """
    ZinetCore
    ${CONAN_LIBS_GLM}
    """
projectGenerator.add_generator(core)