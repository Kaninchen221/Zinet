#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

namespace zt::engine
{
	class Asset;
	
	struct ZINET_ENGINE_API AssetReference
	{
		friend class AssetsManager;

		AssetReference() = default;
		AssetReference(const AssetReference& other) = default;
		AssetReference(AssetReference&& other) = default;

		AssetReference& operator = (const AssetReference& other) = default;
		AssetReference& operator = (AssetReference&& other) = default;

		~AssetReference() noexcept = default;

		Asset* operator -> () { return asset; }
		const Asset* operator -> () const { return asset; }

		const bool operator == (const AssetReference& other) const { return asset == other.asset; }

		const bool isValid() const { return asset != nullptr; }

	private:

		AssetReference(Asset* newAsset)
			: asset(newAsset) {}

		Asset* asset = nullptr;
	};

}