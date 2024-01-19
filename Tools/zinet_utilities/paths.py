from pathlib import Path


def find_zinet_root_path():
    root_path = Path('.').absolute()
    if root_path.name.startswith("Zinet") or root_path.name == "Zinet":
        return root_path

    for parent in root_path.parents:
        if parent.name.startswith("Zinet") or parent.name == "Zinet":
            return parent
    return None


def get_build_folder_name():
    return "build"


def find_zinet_build_path():
    return find_zinet_root_path() / get_build_folder_name()


def find_zinet_bin_path():
    return find_zinet_build_path() / "bin"


def find_scripts_folder():
    return find_zinet_root_path() / "Scripts"


def find_conan_profiles_folder():
    return find_scripts_folder() / "conan_profiles"
