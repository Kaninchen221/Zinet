import types

import clang.cindex
from clang.cindex import CursorKind
from zinet_preflector.parser_result import *


class Sorter:
    def __init__(self):
        self.reflection_parse_results = []

    def sort(self, parser_result):
        self._sort_internal(parser_result)

    def _sort_internal(self, parser_result):
        for child in parser_result.children:
            if child.cursor.kind == CursorKind.MACRO_INSTANTIATION:
                print(f"Found reflect macro: {child.cursor.displayname} at line: {child.cursor.location.line}")
                self.reflection_parse_results.append(child)
            else:
                # We are expecting that every reflection macro is targeting code that is in the next line
                child_line = child.cursor.location.line
                for reflection_parse_result in self.reflection_parse_results:
                    if child_line == reflection_parse_result.cursor.location.line + 1:
                        child.reflection_cursor = reflection_parse_result.cursor

            self._sort_internal(child)

