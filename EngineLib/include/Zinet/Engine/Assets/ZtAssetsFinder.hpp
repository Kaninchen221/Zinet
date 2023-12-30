#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Core/ZtLogger.h"

#include <filesystem>

namespace zt::engine
{
	class ZINET_ENGINE_API AssetsFinder
	{
		inline static auto Logger = core::ConsoleLogger::Create("AssetsFinder");

	public:

		AssetsFinder() = default;
		AssetsFinder(const AssetsFinder& other) = default;
		AssetsFinder(AssetsFinder&& other) = default;

		AssetsFinder& operator = (const AssetsFinder& other) = default;
		AssetsFinder& operator = (AssetsFinder&& other) = default;

		~AssetsFinder() noexcept = default;

		void setContentFolderRootPath(const std::filesystem::path& path) { contentFolderRootPath = path; }
		const std::filesystem::path& getContentFolderRootPath() const { return contentFolderRootPath; }

		void setAssetsMetaFilePostfix(const std::string_view& postfix) { assetsMetaFilePostfix = postfix; }
		const std::string& getAssetsMetaFilePostfix() const { return assetsMetaFilePostfix; }

		std::vector<std::filesystem::directory_entry> findAllAssetsMetaData() const;

	protected:

		std::filesystem::path contentFolderRootPath;
		std::string assetsMetaFilePostfix = ".meta";

	};


}