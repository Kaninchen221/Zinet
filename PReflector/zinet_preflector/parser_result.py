from enum import Enum


class ParserResult:
    def __init__(self):
        self.cursor = None
        self.children = []


def print_parser_result(parser_result):
    print("Parser result:")
    _print_parser_result_internal(parser_result, "")


def _print_parser_result_internal(parser_result, spacing):
    display_name = parser_result.cursor.displayname
    if parser_result.cursor.location.file is None:
        kind = "File Root Node"
    else:
        kind = parser_result.cursor.kind
    print(f"{spacing}{display_name} {kind}")
    spacing += "    "
    for child in parser_result.children:
        _print_parser_result_internal(child, spacing)
    spacing = spacing[:-4]
