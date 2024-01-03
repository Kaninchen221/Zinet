from pathlib import Path

from zinet_reflector.entry_point_main import EntryPointMain


class TestEntryPointMain:

    def test_entry_point_main(self):
        project_root_folder_path = Path('.').absolute()
        entry_point_main_folder_path = Path('.').absolute() / r"test_files\main"
        include_absolute_paths = [r'C:\Fake\include', r'C:\Fake\include']
        entry_point_main = EntryPointMain()
        entry_point_main.create_main(project_root_folder_path, entry_point_main_folder_path, include_absolute_paths)

        assert entry_point_main.main_file_path.is_file()
