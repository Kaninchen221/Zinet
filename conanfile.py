from conans import ConanFile, CMake

class ZinetConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = [
        "gtest/1.10.0@",
        "spdlog/1.9.2@",
        "plf_colony/6.25@",
        "imgui/1.86@",
        "glfw/3.3.6@",
        "stb/20200203@",
        "pybind11/2.9.1@",
        "nlohmann_json/3.10.5@",
        "box2d/2.4.1@",
        "glm/0.9.9.5@"
        ]
   generators = "cmake"
   default_options = {"gtest:shared": True}

   def imports(self):
      self.copy("*.pdb", dst="*", src="lib")
