from pathlib import Path
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

        code_generator = CodeGenerator()
        generated_code = code_generator.generate_code(parser_result)
