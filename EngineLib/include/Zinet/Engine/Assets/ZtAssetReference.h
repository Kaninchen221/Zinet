#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

namespace zt::engine
{
	class Asset;
	
	struct ZINET_ENGINE_API AssetReference
	{
		friend class AssetsManager;

		AssetReference(bool newSuccess, Asset* newAsset);
		AssetReference() = default;
		AssetReference(const AssetReference& other) = default;
		AssetReference(AssetReference&& other) = default;

		AssetReference& operator = (const AssetReference& other) = default;
		AssetReference& operator = (AssetReference&& other) = default;

		~AssetReference() noexcept = default;
		
		const bool isValid = false;

		Asset* operator -> () { return asset; }
		const Asset* operator -> () const { return asset; }

	private:

		Asset* asset;

	};
}