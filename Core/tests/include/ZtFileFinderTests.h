#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtFileFinder.h"

namespace zt::tests
{

	class FileFinderTests : public ::testing::Test
	{
	protected:

		FileFinder fileFinder;

	};

	TEST_F(FileFinderTests, PrintDebugInfoTest)
	{
		fileFinder.printDebugInfo();
	}

	TEST_F(FileFinderTests, CurrentPathTest)
	{
		FileFinder::Path path = fileFinder.currentPath();
		ASSERT_FALSE(path.empty());
	}

	TEST_F(FileFinderTests, CurrentProjectRootPathTest)
	{
		FileFinder::Path path = fileFinder.currentProjectRootPath();
		ASSERT_FALSE(path.empty());
	}

	TEST_F(FileFinderTests, FindFilesInSpecificFolderTest)
	{
		FileFinder::Path folderName = "file_finder_test_folder";
		FileFinder::Path path = fileFinder.currentProjectRootPath();
		path /= folderName;
		FileFinder::FolderInfo files = fileFinder.findFiles(path);

		size_t expectedFilesCount = 3u;
		size_t actualFilesCount = files.size();
		ASSERT_EQ(actualFilesCount, expectedFilesCount);
	}

	TEST_F(FileFinderTests, FindFilesInSpecificFolderWithSpecificExtensionTest)
	{
		FileFinder::Path folderName = "file_finder_test_folder";
		FileFinder::Path path = fileFinder.currentProjectRootPath();
		path /= folderName;
		FileFinder::Extension extension = ".txt2";

		FileFinder::FolderInfo files = fileFinder.findFiles(path, extension);
		size_t expectedFilesCount = 2u;
		size_t actualFilesCount = files.size();
		ASSERT_EQ(actualFilesCount, expectedFilesCount);
	}

}