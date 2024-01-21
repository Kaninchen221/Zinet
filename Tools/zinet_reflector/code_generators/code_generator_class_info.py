from zinet_reflector.code_generator import CodeGeneratorInstructionBase
from zinet_reflector.parser_result import ReflectionKind


class CodeGeneratorClassInfo(CodeGeneratorInstructionBase):
    def __init__(self):
        super().__init__()
        self.token = None
        self.class_name = None
        self.members = []

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

        if parser_result.reflection_kind == ReflectionKind.Member:
            self.members.append(parser_result)

    def generate_code_post(self, file_path):
        return self.generate_get_all_members(file_path)

    def generate_get_all_members(self, file_path):
        generated_code = "\nauto getAllMembers() { return std::make_tuple("
        for member in self.members:
            if member.cursor.location.file.name != file_path:
                continue

            generated_code += f"{member.get_member_name()}, "
        generated_code = generated_code[:-2]
        generated_code += "); };"
        return generated_code
