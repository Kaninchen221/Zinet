from zinet_reflector.parser import *
from zinet_reflector.reflector import Reflector


class TestReflector:

    def test_reflector(self):
        print('')
        folder_contains_main = Path(".").absolute() / "test_files"
        project_root_folder = folder_contains_main
        reflector = Reflector()
        reflector.reflect(folder_contains_main, project_root_folder)
