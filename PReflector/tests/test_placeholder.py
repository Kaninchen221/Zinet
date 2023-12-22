from zinet_preflector.placeholder import *


class TestPlaceholder:

    def test_placeholder(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parse_result = parser.parse(path)

