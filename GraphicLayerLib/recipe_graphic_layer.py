from zinet_generator.cmakelists_generator_library import CMakeListsGeneratorLibrary

graphicLayer = CMakeListsGeneratorLibrary()
graphicLayer.targetName = "ZinetGraphicLayer"
graphicLayer.targetPrettyName = "Zinet Graphic Layer"
graphicLayer.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    ZINET_LIB
    """
graphicLayer.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_SHADERC}
    ${CONAN_INCLUDE_DIRS_GLFW}
    ${CONAN_INCLUDE_DIRS_GLM}
    ${CONAN_INCLUDE_DIRS_STB}
    ${CONAN_INCLUDE_DIRS_VULKAN-MEMORY-ALLOCATOR}
    ${Vulkan_INCLUDE_DIRS}
    """
graphicLayer.linkLibraries = """
    ZinetCore
    ZinetWindow
    ZinetMath
    ImGui
    ${CONAN_LIBS_SHADERC}
    ${CONAN_LIBS_GLFW}
    ${CONAN_LIBS_GLM}
    ${CONAN_LIBS_GLSLANG}
    ${CONAN_LIBS_STB}
    ${CONAN_LIBS_VULKAN-MEMORY-ALLOCATOR}
    ${Vulkan_LIBRARIES}
    ${CONAN_LIBS_SPIRV-TOOLS}
    ${CONAN_LIBS_SPIRV-HEADERS}
    """
project_generator.add_generator(graphicLayer)