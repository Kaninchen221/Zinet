from pathlib import Path
from enum import Enum
import clang.cindex


class Parser:
    _root_cursor = {}
    _ignored_cursor_kinds = [clang.cindex.CursorKind.MACRO_DEFINITION, clang.cindex.CursorKind.INCLUSION_DIRECTIVE]

    def _parse_internal(self, parent_cursor):
        for child_cursor in parent_cursor.get_children():
            if child_cursor.kind in self._ignored_cursor_kinds:
                continue

            print(child_cursor.displayname, child_cursor.kind)
            self._parse_internal(child_cursor)

    def parse(self, path):
        parser = clang.cindex.Index.create()
        options = (clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD +
                   clang.cindex.TranslationUnit.PARSE_INCOMPLETE +
                   clang.cindex.TranslationUnit.PARSE_PRECOMPILED_PREAMBLE +
                   clang.cindex.TranslationUnit.PARSE_CACHE_COMPLETION_RESULTS +
                   clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES +
                   clang.cindex.TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION)
        parse_result = parser.parse(path, None, None, options)

        print("")  # For pytest

        # Handling parse error
        # if parse_result.diagnostics:
        # print("Diagnostics in parse_result is not empty")
        # assert False

        self._root_cursor = parse_result.cursor
        if not self._root_cursor.get_children():
            print("Cursor.get_children returned empty")
            assert False

        self._parse_internal(self._root_cursor)
