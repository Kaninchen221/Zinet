import pathlib
import string

class ZtFileGenerator():

    header_template_path = "PPG/Templates/lib_header_template.txt"
    source_template_path = "PPG/Templates/lib_source_template.txt"
    test_template_path = "PPG/Templates/lib_test_header_template.txt"

    _header_template = ""
    _source_template = ""
    _test_template = ""

    _target = None

    # Target dirs
    _full_header_dir = pathlib.Path()
    _full_source_dir = pathlib.Path()
    _full_test_dir = pathlib.Path()

    # Arguments
    _lib_main_header_path = ""
    _lib_namespace = ""
    _lib_api_macro = ""
    _class_name = ""
    _class_header_path = ""
    _lib_test_namespace = ""
    _class_name_lower_case = ""
    _test_class_name = ""

    def generate_class(self, target_name, class_name, generate_test_file, root):
        print("Generate class: " + class_name + " for target: " + target_name)

        self.find_target(target_name, root)
        if self._target == None:
            return False

        if self.found_dirs() == False:
            return False

        self.prepare_arguments(class_name)

        self._header_template = ZtFileGenerator.get_template(ZtFileGenerator.header_template_path)
        self._source_template = ZtFileGenerator.get_template(ZtFileGenerator.source_template_path)
        self._test_template = ZtFileGenerator.get_template(ZtFileGenerator.test_template_path)

        return True


    def find_target(self, target_name, root):
        for target_lib in root.get_targets_libs():
            if target_name == target_lib.name:
                print("Found target!")
                self._target = target_lib

        return None

    def found_dirs(self):
        self._full_header_dir = pathlib.Path().resolve() / self._target.header_path / "Zinet" / self._target.folder_name
        if self._full_header_dir.is_dir():
            print("Full header dir path: ", self._full_header_dir)
        else:
            print("Can't get full header dir path: ", self._full_header_dir)
            return False

        self._full_source_dir = pathlib.Path().resolve() / self._target.source_path
        if self._full_source_dir.is_dir():
            print("Full source dir path: ", self._full_source_dir)
        else:
            print("Can't get full source dir path: ", self._full_source_dir)
            return False

        self._full_test_dir = pathlib.Path().resolve() / self._target.folder_name / self._target.test_subfolder / "include"
        if self._full_test_dir.is_dir():
            print("Full test dir path: ", self._full_test_dir)
        else:
            print("Can't get full test dir path: ", self._full_test_dir)
            return False

        return True;

    def prepare_arguments(self, class_name):
        self._lib_main_header_path = self._target.main_header
        self._lib_namespace = self._target.namespace
        self._lib_api_macro = "ZINET_" + self._target.folder_name.upper() + "_API"
        self._class_name = class_name
        class_header_name = "Zt" + class_name
        self._class_header_path = self._full_header_dir / ("Zt" + class_name + ".h")
        self._lib_test_namespace = self._lib_namespace + "::tests"
        self._class_name_lower_case = class_name[0].lower() + class_name[1:]
        self._test_class_name = class_name + "Tests"

    def get_template(template_path):
        file = open(template_path, mode='r')
        return file.read()
