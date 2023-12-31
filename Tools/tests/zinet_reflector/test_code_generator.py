from pathlib import Path

from zinet_reflector.code_generators.code_generator_class_info import CodeGeneratorClassInfo
from zinet_reflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_reflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_reflector.code_generators.code_generator_operators import CodeGeneratorOperators
from zinet_reflector.parser import *
from zinet_reflector.assignor import *
from zinet_reflector.tokens_finder import *
from zinet_reflector.code_generator import *


class TestCodeGenerator:

    def test_generate_code(self):
        project_root_folder = Path(".").absolute() / "test_files"
        path_to_main = Path(".").absolute() / r"test_files\include\zinet\lib_name\main.cpp"
        parser = Parser()
        parse_result = parser.parse(path_to_main, project_root_folder)

        assignor = Assignor()
        assignor.assign(parse_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parse_result)

        #print("Parse result after assigning:")
        #print_parser_result(parser_result)

        code_generator = CodeGenerator()
        code_generator.instructions.append(CodeGeneratorConstructors())
        code_generator.instructions.append(CodeGeneratorOperators())
        code_generator.instructions.append(CodeGeneratorGetterSetter())
        code_generator.instructions.append(CodeGeneratorClassInfo())

        generated_code = code_generator.generate_code(parse_result)

        print("Generated code:")
        print(generated_code)
        print_generated_code(generated_code)

        assert generated_code
