from pathlib import Path

from zinet_preflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_preflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_preflector.parser import *
from zinet_preflector.assignor import *
from zinet_preflector.tokens_finder import *
from zinet_preflector.code_generator import *


class TestCodeGenerator:

    def test_generate_code(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parser_result = parser.parse(path)

        assignor = Assignor()
        assignor.sort(parser_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parser_result)

        #print("Parse result after assigning:")
        #print_parser_result(parser_result)

        code_generator = CodeGenerator()
        code_generator.instructions.append(CodeGeneratorConstructors())
        code_generator.instructions.append(CodeGeneratorGetterSetter())

        generated_code = code_generator.generate_code(parser_result)

        print("Generated code:")
        print(generated_code)
        print_generated_code(generated_code)
