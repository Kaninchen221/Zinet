from pathlib import Path
from zinet_preflector.parser import *


class TestParser:

    def test_parser(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parser_result = parser.parse(path)
        print("Parser result:")
        print_parser_result(parser_result)
        assert parser_result.children
