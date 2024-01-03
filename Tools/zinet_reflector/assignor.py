import types

from zinet_reflector.parser_result import *


class Assignor:
    def __init__(self):
        self.reflection_parse_results = []
        self._assigned_reflections = 0

    def assign(self, parser_result):
        self._assign_internal(parser_result)
        print(f"Assigned reflections: {self._assigned_reflections}")

    def _assign_internal(self, parser_result):
        for child in parser_result.children:
            if child.cursor.kind == CursorKind.MACRO_INSTANTIATION:
                self.reflection_parse_results.append(child)
            else:
                # We are expecting that every reflection macro is targeting code that is in the next line
                child_line = child.cursor.location.line
                child_file = child.cursor.location.file
                for reflection_parse_result in self.reflection_parse_results:
                    if (child_line == reflection_parse_result.cursor.location.line + 1 and
                            child_file.name == reflection_parse_result.cursor.location.file.name):
                        child.reflection_cursor = reflection_parse_result.cursor
                        try:
                            child.reflection_kind = ReflectionKind(child.reflection_cursor.displayname)
                        except KeyError:
                            pass
                        except ValueError:
                            pass
                        else:
                            self._assigned_reflections += 1

            self._assign_internal(child)
