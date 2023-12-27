from pathlib import Path

from zinet_preflector.code_generators.code_generator_class_info import CodeGeneratorClassInfo
from zinet_preflector.code_generators.code_generator_constructors import CodeGeneratorConstructors
from zinet_preflector.code_generators.code_generator_getter_setter import CodeGeneratorGetterSetter
from zinet_preflector.code_generators.code_generator_operators import CodeGeneratorOperators
from zinet_preflector.parser import *
from zinet_preflector.assignor import *
from zinet_preflector.tokens_finder import *
from zinet_preflector.code_generator import *


class TestCodeGenerator:

    def test_generate_code(self):
        path = str(Path(".").absolute() / "test_files/include/zinet/lib_name/reflection_test_file.hpp")
        parser = Parser()
        parser_result = parser.parse(path)

        assignor = Assignor()
        assignor.sort(parser_result)

        tokens_finder = TokensFinder()
        tokens_finder.find_tokens(parser_result)

        #print("Parse result after assigning:")
        #print_parser_result(parser_result)

        code_generator = CodeGenerator()
        code_generator.instructions.append(CodeGeneratorConstructors())
        code_generator.instructions.append(CodeGeneratorOperators())
        code_generator.instructions.append(CodeGeneratorGetterSetter())
        code_generator.instructions.append(CodeGeneratorClassInfo())

        generated_code = code_generator.generate_code(parser_result)

        print("Generated code:")
        print(generated_code)
        print_generated_code(generated_code)

        expected_generated_code = ['\nTextureAsset() = default;\nTextureAsset(const TextureAsset& other) = default;\nTextureAsset(TextureAsset&& other) = default;\n\n~TextureAsset() noexcept = default;', '\nTextureAsset& operator = (const TextureAsset& other) = default;\nTextureAsset& operator = (TextureAsset&& other) = default;', '\nconst decltype(texture)& getTexture() const { return texture; }', '\nconst decltype(backupTexture)& getBackupTexture() const { return backupTexture; }\nvoid setBackupTexture(const decltype(backupTexture)& newValue) { backupTexture = newValue; }', '\nclass ClassInfo \n{\npublic:\n    static std::string_view GetClassName() const { return "TextureAsset"; }\n};']
        assert generated_code == expected_generated_code
