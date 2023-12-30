import os
from pathlib import Path

from zinet_reflector.assignor import Assignor
from zinet_reflector.code_generator import CodeGenerator
from zinet_reflector.code_generators.code_generator_class_info import CodeGeneratorClassInfo
from zinet_reflector.code_injector import CodeInjector
from zinet_reflector.parser import Parser
from zinet_reflector.tokens_finder import TokensFinder

from zinet_reflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_reflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_reflector.code_generators.code_generator_operators import CodeGeneratorOperators


class Reflector:
    def __init__(self):
        self.main_name = "main.cpp"
        self.found_file_path = ""

    def reflect(self, folder_contains_main_file, project_root_folder):
        print(f"Find {self.main_name} under path: {folder_contains_main_file}")
        self._find_file_for_reflection(folder_contains_main_file)
        print(f"Found at: {self.found_file_path}")
        self._reflect_internal(project_root_folder)

    def _find_file_for_reflection(self, path):
        for root, dirs, files in os.walk(path):
            for file in files:
                if file == self.main_name:
                    self.found_file_path = root + '/' + file

    def _reflect_internal(self, project_root_folder):
        raw_file_path = str(self.found_file_path)
        parser = Parser()
        parse_result = parser.parse(raw_file_path, project_root_folder)

        assignor = Assignor()
        #assignor.sort(parse_result)

        #tokens_finder = TokensFinder()
        #tokens_finder.find_tokens(parse_result)

        #code_generator = CodeGenerator()
        #code_generator.instructions.append(CodeGeneratorConstructors())
        #code_generator.instructions.append(CodeGeneratorOperators())
        #code_generator.instructions.append(CodeGeneratorGetterSetter())
        #code_generator.instructions.append(CodeGeneratorClassInfo())

        #generated_code = code_generator.generate_code(parse_result)

        #code_injector = CodeInjector()
        #try:
            #code_injector.inject_code(file_path, generated_code)
            #self.files_with_generated_code.append(file_path)
            #print("Reflected file: ", file_path)
        #except ValueError:
            #print("Ignored file: ", file_path)
