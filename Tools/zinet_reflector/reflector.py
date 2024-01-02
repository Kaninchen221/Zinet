import concurrent.futures
import os
from pathlib import Path

import clang

from zinet_reflector.assignor import Assignor
from zinet_reflector.code_generator import CodeGenerator, print_generated_code
from zinet_reflector.code_generators.code_generator_class_info import CodeGeneratorClassInfo
from zinet_reflector.code_injector import CodeInjector
from zinet_reflector.parser import Parser
from zinet_reflector.parser_result import print_parser_result
from zinet_reflector.tokens_finder import TokensFinder

from zinet_reflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_reflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_reflector.code_generators.code_generator_operators import CodeGeneratorOperators


class Reflector:

    _libclang_dll_path = Path(".").absolute().parent / "libclang.dll"

    def __init__(self):
        self.main_name = "main.cpp"
        self.found_file_paths = []

    def reflect(self, folder_contains_main_file, project_root_folder):
        print(f"Find {self.main_name} under path: {folder_contains_main_file}")
        self.found_file_paths = self._find_file_for_reflection(folder_contains_main_file)
        print(f"Found at: {self.found_file_paths}")
        self._reflect_files_internal([self.found_file_paths], project_root_folder)

    def _find_file_for_reflection(self, path):
        for root, dirs, files in os.walk(path):
            for file in files:
                if file == self.main_name:
                    return root + '/' + file

    def reflect_multiple(self, project_root_folder):
        print(f"Find multiple {self.main_name} under path: {project_root_folder}")
        self.found_file_paths = self._find_files_for_reflection(project_root_folder)
        print(f"Found at: {' '.join(self.found_file_paths)}")
        self._reflect_files_internal(self.found_file_paths, project_root_folder)

    def _find_files_for_reflection(self, path):
        found_file_paths = []
        for root, dirs, files in os.walk(path):
            for file in files:
                if file == self.main_name:
                    found_file_paths.append(root + '/' + file)
        return found_file_paths

    def _reflect_files_internal(self, files_paths, project_root_folder):
        results = []
        with concurrent.futures.ProcessPoolExecutor() as executor:
            for file_path in files_paths:
                result = executor.submit(self._reflect_file, file_path, project_root_folder)
                results.append(result)
        pass

    @staticmethod
    def _reflect_file(file_path, project_root_folder):
        print(f"Start reflection for file: {file_path}")
        Reflector.load_libclang_dll(Reflector._libclang_dll_path)

        raw_file_path = str(file_path)
        parser = Parser()
        parse_result = parser.parse(raw_file_path, project_root_folder)

        assignor = Assignor()
        assignor.assign(parse_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parse_result)

        print_parser_result(parse_result)

        code_generator = CodeGenerator()
        code_generator.instructions.append(CodeGeneratorConstructors())
        code_generator.instructions.append(CodeGeneratorOperators())
        code_generator.instructions.append(CodeGeneratorGetterSetter())
        code_generator.instructions.append(CodeGeneratorClassInfo())

        generated_code = code_generator.generate_code(parse_result)
        # print_generated_code(generated_code)

        code_injector = CodeInjector()
        code_injector.inject_code(generated_code)
        print(f"End reflection for file: {file_path}")

    @staticmethod
    def load_libclang_dll(library_path):
        library_raw_path = str(library_path)
        clang.cindex.Config.set_library_file(library_raw_path)
        #print(f"libclang.dll path: {library_raw_path}")
