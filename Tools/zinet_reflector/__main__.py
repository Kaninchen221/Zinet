from pathlib import Path

import clang

from zinet_reflector.reflector import Reflector

if __name__ == '__main__':
    library_path = str(Path(".").absolute() / "libclang.dll")
    clang.cindex.Config.set_library_file(library_path)
    print(library_path)

    reflector = Reflector()
    path = Path('.').absolute().parent
    print(path)
    reflector.reflect_recursive(path)
