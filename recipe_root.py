from pg.cmakelists_generator_root import CMakelistsGeneratorRoot

root = CMakelistsGeneratorRoot()
root.cmakeMinimumVersion = "3.20"
root.projectDescription = "Game Engine"
root.projectName = "Zinet"
root.projectVersion = "0.1.2"
#root.subdirectories = ["EntryPoint"]
root.subdirectories = ["Core", "GraphicLayer", "EntryPoint"]
root.globalCompileOptions = "/W4 /WX /external:W0 /external:anglebrackets /MP"
root.globalCompileOptionsForAddressSanitizer = "/fsanitize=address /RTCu /experimental:module-"
root.globalCompileDefinitions = "ZINET_STATIC ZINET_WINDOWS _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION"
projectGenerator.add_generator(root)