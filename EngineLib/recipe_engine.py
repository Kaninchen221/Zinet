from zinet_pgenerator.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetName = "ZinetEngine"
core.targetPrettyName = "Zinet Engine"
core.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    ZINET_LIB
    """
core.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    ${CONAN_INCLUDE_DIRS_PLF_COLONY}
    ${CONAN_INCLUDE_DIRS_FMT}
    """
core.linkLibraries = """
    ZinetGraphicLayer
    ${CONAN_LIBS_GTEST}
    ${CONAN_LIBS_SPDLOG}
    ${CONAN_LIBS_FMT}
    """
projectGenerator.add_generator(core)