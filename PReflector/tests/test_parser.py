from zinet_preflector.parser import *


class TestParser:

    def test_parser(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parse_result = parser.parse(path)

