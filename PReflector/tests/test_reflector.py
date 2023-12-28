from pathlib import Path
from zinet_preflector.parser import *
from zinet_preflector.reflector import Reflector


class TestReflector:

    def test_reflector(self):
        print('')
        path = Path(".").absolute() / "test_files"
        reflector = Reflector()
        reflector.reflect_recursive(path)
        assert len(reflector.files_with_generated_code) == 2
