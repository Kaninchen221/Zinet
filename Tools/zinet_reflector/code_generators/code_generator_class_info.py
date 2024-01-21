from zinet_reflector.code_generator import CodeGeneratorInstructionBase
from zinet_reflector.parser_result import ReflectionKind


class CodeGeneratorClassInfo(CodeGeneratorInstructionBase):
    def __init__(self):
        super().__init__()
        # self.reflection_kind = ReflectionKind.Class
        self.token = None
        self.class_name = None

    def generate_code(self, parser_result):
        if parser_result.reflection_kind == ReflectionKind.Class:
            self.class_name = parser_result.get_class_name()
            get_class_name = f'    static std::string_view GetClassName() {{ return "{self.class_name}"; }}'

            return (f""
                    "\nclass ClassInfo "
                    "\n{"
                    "\npublic:"
                    f"\n{get_class_name}"
                    "\n};")

    def generate_code_post(self, parser_result):
        if parser_result.reflection_kind == ReflectionKind.Class:
            return f"Bleble"
