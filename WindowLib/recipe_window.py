from zinet_generator.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetName = "ZinetWindow"
core.targetPrettyName = "Zinet Window"
core.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    ZINET_LIB
    """
core.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_SPDLOG}
    ${CONAN_INCLUDE_DIRS_FMT}
    ${CONAN_INCLUDE_DIRS_GLFW}
    ${CONAN_INCLUDE_DIRS_GLM}
    """
core.linkLibraries = """
    ZinetCore
    ZinetMath
    ${CONAN_LIBS_SPDLOG}
    ${CONAN_LIBS_FMT}
    ${CONAN_LIBS_GLFW}
    ${CONAN_LIBS_GLM}
    """
project_generator.add_generator(core)