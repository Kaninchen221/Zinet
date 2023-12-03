#include "Zinet/Engine/Assets/ZtAssetsManager.h"

namespace zt::engine
{
	void AssetsManager::addAsset(const std::string& contentPath, const Asset& asset)
	{
		assets.insert({ contentPath, asset });
	}

	AssetReference AssetsManager::getAsset(const std::string& contentPath)
	{
		auto it = assets.find(contentPath);
		const bool found = it != assets.end();

		if (found)
			return AssetReference{ &(it->second) };
		else
			return AssetReference{ nullptr };
	}

}