from pathlib import Path


from zinet_reflector.reflector import Reflector

if __name__ == '__main__':

    reflector = Reflector()
    project_root_folder_path = Path('.').absolute().parent.parent
    assert project_root_folder_path.name == "Zinet"
    folder_for_temp_main = project_root_folder_path / "Tools"
    exceptions_paths = [folder_for_temp_main]
    print(f"Project root folder: {project_root_folder_path}")
    reflector.load_lib_clang_dll()
    reflector.reflect(project_root_folder_path, folder_for_temp_main, exceptions_paths)
