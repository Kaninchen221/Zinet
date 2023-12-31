from zinet_reflector.parser import *
from zinet_reflector.assignor import *


class TestAssignor:

    def test_assignor(self):
        project_root_folder = Path(".").absolute() / "test_files"
        path_to_main = Path(".").absolute() / r"test_files\include\zinet\lib_name\main.cpp"
        parser = Parser()
        parser_results = parser.parse(path_to_main, project_root_folder)

        assignor = Assignor()
        assignor.assign(parser_results)
        print("Parse result after assigning:")
        print_parser_result(parser_results)

        namespace_zt = parser_results.children[17]
        assert len(namespace_zt.children) == 1

        namespace_engine = namespace_zt.children[0]
        assert len(namespace_engine.children) == 1

        class_texture_asset = namespace_engine.children[0]
        assert class_texture_asset.reflection_cursor is not None

        class_texture_asset_logger = class_texture_asset.children[0]
        assert class_texture_asset_logger.reflection_cursor is None

        struct_create_input_info = class_texture_asset.children[1]
        assert struct_create_input_info.reflection_cursor is not None
        assert len(struct_create_input_info.children) == 1
