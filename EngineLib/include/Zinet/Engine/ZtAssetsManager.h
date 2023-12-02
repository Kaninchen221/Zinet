#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"
#include "Zinet/Engine/ZtAsset.h"

#include "Zinet/Core/ZtLogger.h"

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

		struct AssetReference
		{
			friend AssetsManager;

			AssetReference(bool newSuccess, AssetsManager::Assets::iterator newIterator);

			const bool success = false;

			Asset* operator -> () { return &iterator->second; }
			const Asset* operator -> () const { return &iterator->second; }

		private:

			AssetsManager::Assets::iterator iterator;

		};

	public:

		AssetsManager() = default;
		AssetsManager(const AssetsManager& other) = default;
		AssetsManager(AssetsManager&& other) = default;

		AssetsManager& operator = (const AssetsManager& other) = default;
		AssetsManager& operator = (AssetsManager&& other) = default;

		~AssetsManager() noexcept = default;

		void addAsset(const std::string& contentPath, const Asset& asset);

		AssetReference getAsset(const std::string& contentPath);

	protected:

		Assets assets;

	};

}