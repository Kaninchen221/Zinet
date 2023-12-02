#include "Zinet/Engine/ZtAssetsManager.h"

namespace zt::engine
{
	AssetsManager::AssetReference::AssetReference(bool newSuccess, AssetsManager::Assets::iterator newIterator)
		: success(newSuccess), iterator(newIterator)
	{}

	void AssetsManager::addAsset(const std::string& contentPath, const Asset& asset)
	{
		assets.insert({ contentPath, asset });
	}

	AssetsManager::AssetReference AssetsManager::getAsset(const std::string& contentPath)
	{
		auto it = assets.find(contentPath);
		const bool found = it != assets.end();

		return AssetReference{ found, it };
	}

}