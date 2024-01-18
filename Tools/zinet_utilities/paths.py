from pathlib import Path


def find_zinet_root_path():
    root_path = Path('.').absolute()
    if root_path.name.startswith("Zinet") or root_path.name == "Zinet":
        return root_path

    for parent in root_path.parents:
        if parent.name.startswith("Zinet") or parent.name == "Zinet":
            return parent
    return None
