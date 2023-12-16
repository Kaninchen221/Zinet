from zinet_pgenerator.cmakelists_generator_library import CMakeListsGeneratorLibrary

lib = CMakeListsGeneratorLibrary()
lib.targetName = "ImGui"
lib.targetPrettyName = "Imgui Lib"
lib.compileDefinitions = """
    ZINET_LIB
    """
lib.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_GLFW}
    ${Vulkan_INCLUDE_DIRS}
    """
lib.linkLibraries = """
    ${CONAN_LIBS_GLFW}
    ${Vulkan_LIBRARIES}
    """
projectGenerator.add_generator(lib)