from pathlib import Path
from zinet_preflector.parser import *
from zinet_preflector.assignor import *


class TestAssignor:

    def test_assignor(self):
        path = str(Path(".").absolute() / "test_files/reflection_test_file.hpp")
        parser = Parser()
        parser_results = parser.parse(path)

        assignor = Assignor()
        assignor.sort(parser_results)
        print("Parse result after assigning:")
        print_parser_result(parser_results)

        assert len(parser_results.children) == 10

        namespace_zt = parser_results.children[9]
        assert len(namespace_zt.children) == 1

        namespace_engine = namespace_zt.children[0]
        assert len(namespace_engine.children) == 1

        class_texture_asset = namespace_engine.children[0]
        assert len(class_texture_asset.children) == 7
        assert class_texture_asset.reflection_cursor is not None

        class_texture_asset_logger = class_texture_asset.children[0]
        assert class_texture_asset_logger.reflection_cursor is None

        struct_create_input_info = class_texture_asset.children[2]
        assert struct_create_input_info.reflection_cursor is not None
        assert len(struct_create_input_info.children) == 1
