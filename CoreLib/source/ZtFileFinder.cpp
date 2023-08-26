#include "Zinet/Core/ZtFileFinder.h"

namespace zt::core
{

	void FileFinder::printDebugInfo() const
	{
		Logger->info("Absolute current path: {}", currentPath().string());
	}

	FileFinder::Path FileFinder::currentPath() const
	{
		return std::filesystem::current_path();
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
			Logger->error("{} throw exception: {}", CurrentFunctionName(), exception.what());
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
			Logger->error("{} throw exception: {}", CurrentFunctionName(), exception.what());
		}

		return files;
	}

}