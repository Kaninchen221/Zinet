#include "Zinet/Engine/Assets/ZtAssetsManager.hpp"

namespace zt::engine
{
	AssetReference AssetsManager::addAsset(const std::string& contentPath, const Asset& asset)
	{
		auto insertResult = assets.insert({ contentPath, asset });
		if (insertResult.second)
			return AssetReference{ &insertResult.first->second };
		else
			return AssetReference{ nullptr };
	}

	AssetReference AssetsManager::getAsset(const std::string& contentPath)
	{
		auto it = assets.find(contentPath);
		const bool found = it != assets.end();

		if (found)
			return AssetReference{ &it->second };
		else
			return AssetReference{ nullptr };
	}

}