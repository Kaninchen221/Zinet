from pathlib import Path

from zinet_reflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_reflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_reflector.code_generators.code_generator_operators import CodeGeneratorOperators
from zinet_reflector.code_injector import CodeInjector
from zinet_reflector.parser import *
from zinet_reflector.assignor import *
from zinet_reflector.tokens_finder import *
from zinet_reflector.code_generator import *


class TestCodeInjector:

    def test_inject_code(self):
        path = str(Path(".").absolute() / "test_files/include/zinet/lib_name/reflection_test_file.hpp")
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
        code_generator.instructions.append(CodeGeneratorOperators())
        code_generator.instructions.append(CodeGeneratorGetterSetter())

        generated_code = code_generator.generate_code(parser_result)

        #print("Generated code:")
        #print(generated_code)
        #print_generated_code(generated_code)

        code_injector = CodeInjector()
        code_injector.inject_code(path, generated_code)

        file = open(path, 'r')
        expected_file_path = str(Path(".").absolute() /
                                 "test_files/include/zinet/lib_name/reflection_test_file_expected.h")
        expected_file = open(expected_file_path, 'r')
        file_content = file.read()
        expected_file_content = expected_file.read()
        assert file_content == expected_file_content

    def test_inject_code_file_without_injection_tokens(self):
        path = str(Path(".").absolute()
                   / "test_files/include/zinet/lib_name/reflection_test_file_without_injection_tokens.hpp")
        parser = Parser()
        parser_result = parser.parse(path)

        assignor = Assignor()
        assignor.sort(parser_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parser_result)

        code_generator = CodeGenerator()
        code_generator.instructions.append(CodeGeneratorConstructors())
        code_generator.instructions.append(CodeGeneratorOperators())
        code_generator.instructions.append(CodeGeneratorGetterSetter())

        generated_code = code_generator.generate_code(parser_result)

        code_injector = CodeInjector()
        try:
            code_injector.inject_code(path, generated_code)
        except ValueError:
            print("File hasn't injection tokens (Good)")
        else:
            # inject_code must return exception
            assert False
