#include "Zinet/Engine/Assets/ZtAssetsFinder.hpp"

#include "Zinet/Core/ZtFileFinder.hpp"

namespace zt::engine
{
	std::vector<std::filesystem::directory_entry> AssetsFinder::findAllAssetsMetaData() const
	{
		auto findFilesResult = core::FileFinder::FindFiles(contentFolderRootPath, assetsMetaFilePostfix);
		return findFilesResult;
	}

}