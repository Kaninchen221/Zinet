#include "Zinet/Engine/Assets/ZtAssetsManager.h"

namespace zt::engine
{
	AssetReference::AssetReference(bool newSuccess, Asset* newAsset)
		: success(newSuccess), asset(newAsset)
	{}

	void AssetsManager::addAsset(const std::string& contentPath, const Asset& asset)
	{
		assets.insert({ contentPath, asset });
	}

	AssetReference AssetsManager::getAsset(const std::string& contentPath)
	{
		auto it = assets.find(contentPath);
		const bool found = it != assets.end();

		if (found)
			return AssetReference{ found, &(it->second) };
		else
			return AssetReference{ found, nullptr };
	}

}