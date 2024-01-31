from zinet_reflector.code_generator import CodeGeneratorInstructionBase
from zinet_reflector.parser_result import ReflectionKind


class CodeGeneratorClassInfo(CodeGeneratorInstructionBase):
    def __init__(self):
        super().__init__()
        self.token = None
        self.members = []

    def generate_code(self, parser_result):
        if parser_result.reflection_kind == ReflectionKind.Class:
            class_name = parser_result.get_class_name()
            get_class_name_function = f'    std::string_view getClassName() const override {{ return "{class_name}"; }}'

            return (""
                    f"\nclass {class_name}ClassInfo : public zt::core::reflection::ClassInfo"
                    "\n{"
                    "\npublic:"
                    f"\n{get_class_name_function}"
                    "\n};")

        if parser_result.reflection_kind == ReflectionKind.Member:
            self.members.append(parser_result)

    def generate_code_post(self, file_path):
        return self.get_copy_of_all_members(file_path)

    def get_copy_of_all_members(self, file_path):
        if not self.members:
            return None

        members_str = ""
        for member in self.members:
            if member.cursor.location.file.name != file_path:
                continue
            members_str += f"{member.get_member_name()}, "

        members_str = members_str[:-2] if members_str.endswith(', ') else members_str
        generated_code = f"\nauto getCopyOfAllMembers() {{ return std::make_tuple({members_str}); }};"
        return generated_code
