from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary

core = CMakeListsGeneratorLibrary()
core.targetPrettyName = "Zinet Core"
#core.compileDefinitions = 
core.includeDirectories = """
    ${CONAN_INCLUDE_DIRS_SPDLOG}, 
    ${CONAN_INCLUDE_DIRS_PLF_COLONY}, 
    ${CONAN_INCLUDE_DIRS_FMT}"""
#core.linkLibraries = 
projectGenerator.add_generator(core)