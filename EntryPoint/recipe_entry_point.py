from pg.cmakelists_generator_executable import CMakeListsGeneratorExecutable

entryPoint = CMakeListsGeneratorExecutable()
entryPoint.targetName = "ZinetEntryPoint"
entryPoint.targetPrettyName = "Zinet Entry Point"
entryPoint.compileDefinitions = """
    ZINET_CURRENT_PROJECT_ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}"
    """
entryPoint.includeDirectories = """
    """
entryPoint.linkLibraries = """
    ZinetGraphicLayer
    """
projectGenerator.add_generator(entryPoint)