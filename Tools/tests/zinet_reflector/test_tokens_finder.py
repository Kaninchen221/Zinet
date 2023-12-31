from pathlib import Path
from zinet_reflector.parser import *
from zinet_reflector.assignor import *
from zinet_reflector.tokens_finder import *


class TestTokensFinder:

    def test_sorter(self):
        project_root_folder = Path(".").absolute() / "test_files"
        path_to_main = Path(".").absolute() / r"test_files\include\zinet\lib_name\main.cpp"
        parser = Parser()
        parse_result = parser.parse(path_to_main, project_root_folder)

        assignor = Assignor()
        assignor.assign(parse_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parse_result)

        print("Parse result after tokens finder find tokens:")
        print_parser_result(parse_result)
