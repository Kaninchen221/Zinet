from zinet_reflector.code_generator import CodeGeneratorInstructionBase
from zinet_reflector.parser_result import ReflectionKind


class CodeGeneratorClassInfo(CodeGeneratorInstructionBase):
    def __init__(self):
        super().__init__()
        self.token = None
        self.members = []
        self.parser_results = []

    def generate_code(self, parser_result):
        if parser_result.reflection_kind == ReflectionKind.Class:
            self.parser_results.append(parser_result)

        if parser_result.reflection_kind == ReflectionKind.Member:
            self.members.append(parser_result)

    def generate_code_post(self, file_path):
        class_parser_result = None
        for parser_result in self.parser_results:
            if parser_result.get_cursor_file_path() == file_path:
                class_parser_result = parser_result

        if class_parser_result:
            inside = ""
            outside = ""

            if get_class_name_function := self.get_class_name_function(class_parser_result):
                inside += get_class_name_function

            if get_class_info_object := self.get_class_info_object():
                outside += get_class_info_object

            if get_copy_of_all_members := self.get_copy_of_all_members(file_path):
                outside += get_copy_of_all_members

            if get_class_properties_infos := self.get_class_properties_infos(file_path):
                inside += get_class_properties_infos

            class_info = (""
                          f'\nclass ClassInfo : public zt::core::reflection::ClassInfo'
                          '\n{'
                          '\npublic:'
                          f'\n{inside}'
                          '\n};'
                          f'{outside}')

            return class_info

    @staticmethod
    def get_class_name_function(class_parser_result):
        class_name = class_parser_result.get_class_name()
        return f'    std::string_view getClassName() const override {{ return "{class_name}"; }}'

    @staticmethod
    def get_class_info_object():
        result = ("\nstd::unique_ptr<zt::core::reflection::ClassInfo> getClassInfoObject() const { return "
                  "std::make_unique<ClassInfo>(); }")
        return result

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
        return generated_code + "\n"

    def get_class_properties_infos(self, file_path):
        if not self.members:
            return None

        generated_code_begin = (f"\n\tzt::core::reflection::ClassPropertiesInfos getClassPropertiesInfos() override {{ "
                                f"return zt::core::reflection::ClassPropertiesInfos(std::vector{{")
        initializer_list = ""
        class_property_info = "zt::core::reflection::ClassPropertyInfo"
        separator = ',\n\t' + (' ' * (len(generated_code_begin) - 1))
        for member in self.members:
            if member.cursor.location.file.name != file_path:
                continue
            member_name = r'"' + member.get_member_name() + r'"'
            member_class_type_name = member.get_member_class_type_name()
            offset = f"offsetof({member_class_type_name}, {member.get_member_name()})"
            member_type_name = r'"' + member.get_member_type_name() + r'"'
            initializer_list += f"{class_property_info}{{{offset}, {member_name}, {member_type_name}}}{separator}"

        if initializer_list.endswith(separator):
            initializer_list = initializer_list[:-len(separator)]

        generated_code = generated_code_begin + f"{initializer_list}}}); }};"
        return generated_code + "\n"
