from zinet_utilities import paths


class TestUtilities:
    def test_get_zinet_root_path(self):
        zinet_root_path = paths.find_zinet_root_path()
        assert zinet_root_path
        assert zinet_root_path.exists()

        assert zinet_root_path.parent.name != "tests"
        assert zinet_root_path.parent.parent.name != "Tools"

        folder = str(zinet_root_path.name).lower()
        assert folder.startswith('zinet') or folder.endswith('zinet')

