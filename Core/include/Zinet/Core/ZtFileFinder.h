#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"
#include <filesystem>
#include <vector>

class ZtFileFinder
{

public:

	using Path = std::filesystem::path;
	using FileInfo = std::filesystem::directory_entry;
	using Extension = std::filesystem::path;

	void PrintDebugInfo() const;
	
	Path CurrentPath() const;

	Path EngineRootPath() const;

	inline Path CurrentProjectRootPath() const;

	std::vector<FileInfo> FindFiles(Path PathToFolder) const;

	std::vector<FileInfo> FindFiles(Path PathToFolder, Extension NeededExtension) const;

protected:

	inline static std::shared_ptr<spdlog::logger> Logger = spdlog::stdout_color_mt("ZtFileFinder");

};

inline ZtFileFinder::Path ZtFileFinder::CurrentProjectRootPath() const
{
	using MacroType = std::decay_t<decltype(ZINET_CURRENT_PROJECT_ROOT_PATH)>;
	using ValidType = const char*;
	static_assert(std::is_same_v<ValidType, MacroType>, "Macro must have valid type");
	return ZINET_CURRENT_PROJECT_ROOT_PATH;
}