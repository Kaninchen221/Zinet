from pathlib import Path
from zinet_reflector.parser import *


class TestParser:

    def test_parser(self):
        print('')
        project_root_folder = Path(".").absolute() / "test_files"
        path_to_main = Path(".").absolute() / r"test_files\include\zinet\lib_name\main.cpp"
        parser = Parser()
        parse_result = parser.parse(path_to_main, project_root_folder)
        print("Parser result:")
        print_parser_result(parse_result)
        assert parse_result.children
