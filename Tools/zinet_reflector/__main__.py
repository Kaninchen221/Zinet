from pathlib import Path


from zinet_reflector.reflector import Reflector


def find_zinet_folder():
    root_path = Path('.').absolute()
    for parent in root_path.parents:
        if parent.name.startswith("Zinet") or parent.name == "Zinet":
            return parent
    return None


if __name__ == '__main__':
    try:
        reflector = Reflector()
        project_root_folder_path = find_zinet_folder()
        if project_root_folder_path is None:
            raise Exception("Can't find zinet root folder path")

        folder_for_temp_main = project_root_folder_path / "Tools"
        exceptions_paths = [folder_for_temp_main]
        reflector.reflect(project_root_folder_path, folder_for_temp_main, exceptions_paths)
    except Exception as exception:
        print(exception.args)
        exit(1)
