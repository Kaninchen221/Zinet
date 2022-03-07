import os


class ZtGeneratorCMake:

    template_input_file = "Scripts/Templates/CMakeTemplate.txt"

    cmake_output_file_path = "CMakeLists.txt"

    _generated_cmake = ""

    def create_cmake_file(self):
        cmake_file = open(self.cmake_output_file_path, 'w')
        cmake_file.write(self._generated_cmake)
        cmake_file.close()

