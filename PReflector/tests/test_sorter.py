from pathlib import Path
from zinet_preflector.parser import *
from zinet_preflector.sorter import *


class TestSorter:

    def test_sorter(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parser_results = parser.parse(path)
        #print("Parse result before sorting:")
        #print_parser_result(parser_result)

        sorter = Sorter()
        sorter.sort(parser_results)
        print("Parse result after sorting:")
        print_parser_result(parser_results)

        for parser_result in parser_results.children:
            for token in parser_result.cursor.get_tokens():
                print()
            for cursor in parser_result.cursor.get_children():
                print()
