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
        self.extension_suffix = ".hpp"
        self.found_files_paths = []
        self.files_with_generated_code = []

    def reflect_recursive(self, path):
        print(f"Generate reflection recursive for files under path: {path}")
        self._find_files_for_reflection(path)
        self._reflect_recursive_internal()

    def _find_files_for_reflection(self, path):
        for root, dirs, files in os.walk(path):
            for file in files:
                file_path = Path(root + '/' + file)
                if file_path.suffix == self.extension_suffix:
                    self.found_files_paths.append(file_path)

    def _reflect_recursive_internal(self):
        print("Reflect files:")
        for file_path in self.found_files_paths:
            raw_file_path = str(file_path)
            parser = Parser()
            parse_result = parser.parse(raw_file_path)

            assignor = Assignor()
            assignor.sort(parse_result)

            tokens_finder = TokensFinder()
            tokens_finder.find_tokens(parse_result)

            code_generator = CodeGenerator()
            code_generator.instructions.append(CodeGeneratorConstructors())
            code_generator.instructions.append(CodeGeneratorOperators())
            code_generator.instructions.append(CodeGeneratorGetterSetter())
            code_generator.instructions.append(CodeGeneratorClassInfo())

            generated_code = code_generator.generate_code(parse_result)

            code_injector = CodeInjector()
            try:
                code_injector.inject_code(file_path, generated_code)
                self.files_with_generated_code.append(file_path)
                print("Reflected file: ", file_path)
            except ValueError:
                print("Ignored file: ", file_path)
