#include "Zinet/Engine/Assets/ZtAssetsFinder.h"

#include "Zinet/Core/ZtFileFinder.h"

namespace zt::engine
{
	std::vector<std::filesystem::directory_entry> AssetsFinder::findAllAssetsMetaData() const
	{
		auto findFilesResult = core::FileFinder::FindFiles(contentFolderRootPath, assetsMetaFilePostfix);
		return findFilesResult;
	}

}