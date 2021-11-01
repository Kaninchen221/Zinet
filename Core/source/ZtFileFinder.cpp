#include "Zinet/Core/ZtFileFinder.h"

void ZtFileFinder::PrintDebugInfo() const
{
	Logger->info("Absolute current path: {}", CurrentPath().string());
	Logger->info("Absolute engine root path: {}", EngineRootPath().string());
}

ZtFileFinder::Path ZtFileFinder::CurrentPath() const
{
	return std::filesystem::current_path();
}

ZtFileFinder::Path ZtFileFinder::EngineRootPath() const
{
	using MacroType = std::decay_t<decltype(ZINET_ENGINE_ROOT_PATH)>;
	using ValidType = const ZtChar*;
	static_assert(std::is_same_v<ValidType, MacroType>, "Macro must have valid type");
	return ZINET_ENGINE_ROOT_PATH;
}

std::vector<ZtFileFinder::FileInfo> ZtFileFinder::FindFiles(Path PathToFolder) const
{
	std::vector<FileInfo> Files;

	try
	{
		std::filesystem::directory_iterator DirectoryIterator = std::filesystem::directory_iterator(PathToFolder);
		for (std::filesystem::directory_entry DirectoryEntry : DirectoryIterator)
		{
			if (DirectoryEntry.is_regular_file())
			{
				Files.push_back(DirectoryEntry);
			}
		}
	}
	catch (const std::exception& Exception)
	{
		Logger->error("{} throw exception: {}", __FUNCTION__, Exception.what());
	}

	return Files;
}

std::vector<ZtFileFinder::FileInfo> ZtFileFinder::FindFiles(Path PathToFolder, Extension NeededExtension) const
{
	std::vector<FileInfo> Files;

	try
	{
		std::filesystem::directory_iterator DirectoryIterator = std::filesystem::directory_iterator(PathToFolder);
		for (std::filesystem::directory_entry DirectoryEntry : DirectoryIterator)
		{
			if (DirectoryEntry.is_regular_file())
			{
				Path FilePath = DirectoryEntry.path();
				Extension FileExtension = FilePath.extension();

				if (NeededExtension == FileExtension)
				{
					Files.push_back(DirectoryEntry);
				}
			}
		}
	}
	catch (const std::exception& Exception)
	{
		Logger->error("{} throw exception: {}", __FUNCTION__, Exception.what());
	}

	return Files;
}
