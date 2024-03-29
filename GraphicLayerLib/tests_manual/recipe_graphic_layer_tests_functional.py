from zinet_generator.cmakelists_generator_test import CMakeListsGeneratorTest

test = CMakeListsGeneratorTest()
test.targetName = "ZinetGraphicLayerManualTests"
test.targetPrettyName = "Zinet Graphic Layer Manual Tests"
test.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    """
test.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_GTEST}
    """
test.linkLibraries =  """
    ZinetWindow
    ZinetGraphicLayer
    ${CONAN_LIBS_GTEST}
    """
project_generator.add_generator(test)