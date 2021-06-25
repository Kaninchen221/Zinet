#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"
#include <filesystem>
#include <vector>
#include "Zinet/Core/ZtLogger.h"

class ZtFileFinder
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtFileFinder");

public:

	using Path = std::filesystem::path;
	using FileInfo = std::filesystem::directory_entry;
	using FolderInfo = std::vector<FileInfo>;
	using Extension = std::filesystem::path;

	void PrintDebugInfo() const;
	
	Path CurrentPath() const;

	Path EngineRootPath() const;

	inline Path CurrentProjectRootPath() const;

	FolderInfo FindFiles(Path PathToFolder) const;

	FolderInfo FindFiles(Path PathToFolder, Extension NeededExtension) const;

protected:


};

inline ZtFileFinder::Path ZtFileFinder::CurrentProjectRootPath() const
{
	using MacroType = std::decay_t<decltype(ZINET_CURRENT_PROJECT_ROOT_PATH)>;
	using ValidType = const char*;
	static_assert(std::is_same_v<ValidType, MacroType>, "Macro must have valid type");
	return ZINET_CURRENT_PROJECT_ROOT_PATH;
}