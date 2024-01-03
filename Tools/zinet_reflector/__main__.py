from pathlib import Path


from zinet_reflector.reflector import Reflector

if __name__ == '__main__':

    reflector = Reflector()
    project_root_folder = Path('.').absolute().parent.parent
    print(f"Project root folder: {project_root_folder}")
    reflector.load_lib_clang_dll()
    reflector.reflect(None)
