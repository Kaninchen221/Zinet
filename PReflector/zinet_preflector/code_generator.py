import types

import clang.cindex
from clang.cindex import CursorKind
from zinet_preflector.parser_result import *


class CodeGeneratorInstructionBase:
    def __init__(self):
        self.reflection_kind = ReflectionKind.Namespace
        self.token = ""

    def generate_code(self, parser_result):
        return None

    def generate_code_post(self):
        return None


class CodeGenerator:
    def __init__(self):
        self.instructions = []

    def generate_code(self, parser_result):
        generated_code = []
        self._generate_code_internal(parser_result, generated_code)
        self._generate_code_post(parser_result, generated_code)
        return generated_code

    def _generate_code_internal(self, parser_result, generated_code):
        for child_parser_result in parser_result.children:
            for instruction in self.instructions:
                instruction_generated_code = instruction.generate_code(child_parser_result)
                if instruction_generated_code:
                    generated_code.append(instruction_generated_code)
            self._generate_code_internal(child_parser_result, generated_code)

    def _generate_code_post(self, parser_result, generated_code):
        for instruction in self.instructions:
            instruction_generated_code = instruction.generate_code_post()
            if instruction_generated_code:
                generated_code.append(instruction_generated_code)


def print_generated_code(generated_code):
    for code in generated_code:
        print(code)
