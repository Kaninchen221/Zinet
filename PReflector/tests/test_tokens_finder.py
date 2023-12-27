from pathlib import Path
from zinet_preflector.parser import *
from zinet_preflector.assignor import *
from zinet_preflector.tokens_finder import *


class TestTokensFinder:

    def test_sorter(self):
        path = str(Path(".").absolute() / "test_files/include/zinet/lib_name/reflection_test_file.hpp")
        parser = Parser()
        parser_result = parser.parse(path)

        assignor = Assignor()
        assignor.sort(parser_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parser_result)

        print("Parse result after tokens finder find tokens:")
        print_parser_result(parser_result)
