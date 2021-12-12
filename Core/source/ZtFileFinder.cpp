#include "Zinet/Core/ZtFileFinder.h"

namespace zt
{

	void FileFinder::printDebugInfo() const
	{
		Logger->info("Absolute current path: {}", currentPath().string());
		Logger->info("Absolute engine root path: {}", engineRootPath().string());
	}

	FileFinder::Path FileFinder::currentPath() const
	{
		return std::filesystem::current_path();
	}

	FileFinder::Path FileFinder::engineRootPath() const
	{
		using MacroType = std::decay_t<decltype(ZINET_ENGINE_ROOT_PATH)>;
		using ValidType = const char*;
		static_assert(std::is_same_v<ValidType, MacroType>, "Macro must have valid type");
		return ZINET_ENGINE_ROOT_PATH;
	}

	std::vector<FileFinder::FileInfo> FileFinder::findFiles(Path pathToFolder) const
	{
		std::vector<FileInfo> files;

		try
		{
			std::filesystem::directory_iterator directoryIterator = std::filesystem::directory_iterator(pathToFolder);
			for (std::filesystem::directory_entry directoryEntry : directoryIterator)
			{
				if (directoryEntry.is_regular_file())
				{
					files.push_back(directoryEntry);
				}
			}
		}
		catch (const std::exception& exception)
		{
			Logger->error("{} throw exception: {}", __FUNCTION__, exception.what());
		}

		return files;
	}

	std::vector<FileFinder::FileInfo> FileFinder::findFiles(Path pathToFolder, Extension neededExtension) const
	{
		std::vector<FileInfo> files;

		try
		{
			std::filesystem::directory_iterator directoryIterator = std::filesystem::directory_iterator(pathToFolder);
			for (std::filesystem::directory_entry directoryEntry : directoryIterator)
			{
				if (directoryEntry.is_regular_file())
				{
					Path filePath = directoryEntry.path();
					Extension fileExtension = filePath.extension();

					if (neededExtension == fileExtension)
					{
						files.push_back(directoryEntry);
					}
				}
			}
		}
		catch (const std::exception& exception)
		{
			Logger->error("{} throw exception: {}", __FUNCTION__, exception.what());
		}

		return files;
	}

}