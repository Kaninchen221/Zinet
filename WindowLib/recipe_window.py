from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetName = "ZinetWindow"
core.targetPrettyName = "Zinet Window"
core.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    """
core.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    ${CONAN_INCLUDE_DIRS_FMT}
    ${CONAN_INCLUDE_DIRS_GLFW}
    ${CONAN_INCLUDE_DIRS_GLM}
    """
core.linkLibraries = """
    ZinetCore
    ${CONAN_LIBS_SPDLOG}
    ${CONAN_LIBS_FMT}
    ${CONAN_LIBS_GLFW}
    ${CONAN_LIBS_GLM}
    """
projectGenerator.add_generator(core)