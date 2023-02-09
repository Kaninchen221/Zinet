from pg.cmakelists_generator_root import CMakelistsGeneratorRoot

root = CMakelistsGeneratorRoot()
root.cmakeMinimumVersion = "3.20"
root.projectDescription = "Game Engine"
root.projectName = "Zinet"
root.projectVersion = "0.1.2"
#root.subdirectories = ["EntryPoint"]
root.subdirectories = ["Core", "GraphicLayer"]
root.globalCompileDefinitions = "ZINET_STATIC ZINET_WINDOWS"
projectGenerator.add_generator(root)