from enum import Enum
from clang.cindex import CursorKind


class ParserResultKind(Enum):
    Namespace = "ZT_REFLECT_NAMESPACE"
    Class = "ZT_REFLECT_CLASS"
    Struct = "ZT_REFLECT_STRUCT"
    Method = "ZT_REFLECT_METHOD"
    Member = "ZT_REFLECT_MEMBER"


class ParserResult:
    def __init__(self):
        self.cursor = None
        self.reflection_cursor = None
        self.children = []


def print_parser_result(parser_result):
    _print_parser_result_internal(parser_result, "")


def _print_parser_result_internal(parser_result, spacing):
    display_name = parser_result.cursor.displayname

    if parser_result.cursor.location.file is None:
        kind = "File Root Cursor"
    else:
        kind = parser_result.cursor.kind
    line = parser_result.cursor.location.line

    reflect_macro_message = ""
    if parser_result.reflection_cursor is None:
        reflect_macro = "None"
        if parser_result.cursor.location.line != 0:
            if parser_result.cursor.kind != CursorKind.MACRO_INSTANTIATION:
                reflect_macro_message = f"assigned reflect macro: {reflect_macro}"
    else:
        reflect_macro = parser_result.reflection_cursor.displayname
        reflect_macro_line = parser_result.reflection_cursor.location.line
        reflect_macro_message = f"assigned reflect macro: {reflect_macro} from line: {reflect_macro_line}"

    print(f"{spacing}{display_name} {kind} at line: {line} {reflect_macro_message}")
    spacing += "    "
    for child in parser_result.children:
        _print_parser_result_internal(child, spacing)
    spacing = spacing[:-4]
