from zinet_reflector.parser_result import *


class CodeInjector:
    def __init__(self):
        self.token_inject_code_start = "/*GENERATED_CODE_START*/"
        self.token_inject_code_end = "/*GENERATED_CODE_END*/"

    def inject_code(self, file_path, generated_code):
        # Clear the content of file between the code injection tokens
        with (open(file_path, 'r+') as file):
            file_content = file.read()
            inject_code_start_index = (file_content.index(self.token_inject_code_start)
                                       + len(self.token_inject_code_start))
            inject_code_end_index = file_content.index(self.token_inject_code_end)
            # Clear part of file content between tokens
            # file_content = file_content[:inject_code_start_index] + file_content[inject_code_end_index:]

        # Inject generated code
        with open(file_path, 'w') as file:
            generated_code_as_string = ''.join(generated_code)
            file_content = (file_content[:inject_code_start_index]
                            + generated_code_as_string
                            + "\n"
                            + file_content[inject_code_end_index:])
            file.write(file_content)
