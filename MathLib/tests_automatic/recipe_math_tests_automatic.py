from pg.cmakelists_generator_test import CMakeListsGeneratorTest

test = CMakeListsGeneratorTest()
test.targetName = "ZinetMathAutomaticTests"
test.targetPrettyName = "Zinet Math Automatic Tests"
test.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    """
test.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_GTEST}
    """
test.linkLibraries =  """
    ZinetMath
    ${CONAN_LIBS_GTEST}
    """
projectGenerator.add_generator(test)