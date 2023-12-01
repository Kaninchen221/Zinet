from pg.cmakelists_generator_root import CMakelistsGeneratorRoot

root = CMakelistsGeneratorRoot()
root.cmakeMinimumVersion = "3.20"
root.projectDescription = "Game Engine"
root.projectName = "Zinet"
root.projectVersion = "0.1.2"
root.subdirectories = ["CoreLib", "GraphicLayerLib", "EntryPoint", "EngineLib", "WindowLib", "MathLib", "ImGuiLib"]
root.globalCompileOptions = "/W4 /WX /external:W0 /external:anglebrackets /MP"
root.globalCompileOptionsForAddressSanitizer = "/fsanitize=address /RTCu /experimental:module-"
root.globalCompileDefinitions = "ZINET_WINDOWS _DISABLE_VECTOR_ANNOTATION _DISABLE_STRING_ANNOTATION"
projectGenerator.add_generator(root)

from pg.cmakelists_generator_library import CMakeListsGeneratorLibrary

CMakeListsGeneratorLibrary.libraryType = "SHARED"