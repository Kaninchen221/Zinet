from pathlib import Path

from zinet_reflector.parser import *
from zinet_reflector.assignor import *


class TestAssignor:

    def test_assignor(self):
        project_root_folder = Path(".").absolute() / "test_files"
        path = Path(".").absolute() / r"test_files\include\zinet\lib_name\reflection_test_file.hpp"
        parser = Parser()
        parser_results = parser.parse(path)

        assignor = Assignor()
        assignor.assign(parser_results)
        print("Parse result after assigning:")
        print_parser_result(parser_results)
