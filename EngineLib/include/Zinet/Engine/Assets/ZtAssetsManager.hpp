#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"
#include "Zinet/Engine/Assets/ZtAsset.hpp"
#include "Zinet/Engine/Assets/ZtAssetReference.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include <any>
#include <functional>
#include <map>

namespace zt::engine
{
	class ZINET_ENGINE_API AssetsManager
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetsManager");

	public:

		using Assets = std::map<std::string, Asset>;

		AssetsManager() = default;
		AssetsManager(const AssetsManager& other) = default;
		AssetsManager(AssetsManager&& other) = default;

		AssetsManager& operator = (const AssetsManager& other) = default;
		AssetsManager& operator = (AssetsManager&& other) = default;

		~AssetsManager() noexcept = default;

		AssetReference addAsset(const std::string& contentPath, const Asset& asset);

		AssetReference getAsset(const std::string& contentPath);

	protected:

		Assets assets;

	};

}