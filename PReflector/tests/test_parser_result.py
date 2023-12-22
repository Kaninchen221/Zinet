from zinet_preflector.parser_result import *


class TestParserResult:

    parser_result = ParserResult()

    def test_namespace(self):
        assert hasattr(self.parser_result, "cursor")
        assert hasattr(self.parser_result, "children")

