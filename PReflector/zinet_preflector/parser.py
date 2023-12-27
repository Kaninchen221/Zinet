import clang.cindex
from clang.cindex import CursorKind
from zinet_preflector.parser_result import *
from pathlib import Path

class Parser:
    def __init__(self):
        self.root_cursor = {}
        self._ignored_cursor_kinds = [CursorKind.MACRO_DEFINITION, CursorKind.INCLUSION_DIRECTIVE]

    def parse(self, raw_path):
        parser = clang.cindex.Index.create()
        options = self.get_options()
        args = self.get_args(raw_path)
        cindex_parser_result = parser.parse(raw_path, args, unsaved_files=None, options=options)

        print("")  # For pytest

        # Handling parse error
        # if parse_result.diagnostics:
        # print("Diagnostics in parse_result is not empty")
        # assert False

        self.root_cursor = cindex_parser_result.cursor
        if not self.root_cursor.get_children():
            print("Cursor.get_children returned empty")
            assert False

        parser_result = ParserResult()
        parser_result.cursor = self.root_cursor
        self._parse_internal(parser_result)
        return parser_result

    def _parse_internal(self, parent_parser_result):
        for child_cursor in parent_parser_result.cursor.get_children():
            if child_cursor.kind in self._ignored_cursor_kinds:
                continue

            new_parser_result = ParserResult()
            new_parser_result.cursor = child_cursor
            self._parse_internal(new_parser_result)
            parent_parser_result.children.append(new_parser_result)

    @staticmethod
    def get_options():
        return (clang.cindex.TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD +
                clang.cindex.TranslationUnit.PARSE_INCOMPLETE +
                clang.cindex.TranslationUnit.PARSE_PRECOMPILED_PREAMBLE +
                clang.cindex.TranslationUnit.PARSE_CACHE_COMPLETION_RESULTS +
                clang.cindex.TranslationUnit.PARSE_SKIP_FUNCTION_BODIES +
                clang.cindex.TranslationUnit.PARSE_INCLUDE_BRIEF_COMMENTS_IN_CODE_COMPLETION)

    @staticmethod
    def get_args(path):
        args = []
        path = Path(path)
        for parent_path in path.parents:
            if parent_path.name == "include":
                include_path_arg = f"-I{parent_path}"
                args.append(include_path_arg)
                break
        return args
