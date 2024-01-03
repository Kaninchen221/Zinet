from zinet_reflector.parser import *
from zinet_reflector.reflector import Reflector


class TestReflector:

    def test_reflector(self):
        print('')
        project_root_folder_path = Path(".").absolute() / "test_files"
        folder_for_temp_main = Path(".").absolute() / "test_files/main"
        Reflector.libclang_dll_path = Path(".").absolute().parent.parent / "libclang.dll"
        reflector = Reflector()
        #reflector.load_lib_clang_dll()
        reflector.reflect(project_root_folder_path, folder_for_temp_main)
