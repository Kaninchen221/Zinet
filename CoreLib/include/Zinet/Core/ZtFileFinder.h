#pragma once

#include <filesystem>
#include <vector>

#include "Zinet/Core/ZtCoreConfig.h"
#include "Zinet/Core/ZtLogger.h"

namespace zt::core
{

	class ZINET_CORE_API FileFinder
	{
	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Fil Finder");

	public:

		using Path = std::filesystem::path;
		using FileInfo = std::filesystem::directory_entry;
		using FolderInfo = std::vector<FileInfo>;
		using Extension = std::filesystem::path;

		void printDebugInfo() const;

		Path currentPath() const;

		inline Path currentProjectRootPath() const;

		FolderInfo findFiles(Path pathToFolder) const;

		FolderInfo findFiles(Path pathToFolder, Extension neededExtension) const;

	};

	inline FileFinder::Path FileFinder::currentProjectRootPath() const
	{
		using MacroType = std::decay_t<decltype(ZINET_CURRENT_PROJECT_ROOT_PATH)>;
		using ValidType = const char*;
		static_assert(std::is_same_v<ValidType, MacroType>, "Macro must have valid type");
		return ZINET_CURRENT_PROJECT_ROOT_PATH;
	}

}