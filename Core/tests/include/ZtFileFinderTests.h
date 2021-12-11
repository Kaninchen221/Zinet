#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtFileFinder.h"

namespace zt::tests
{

	class FileFinderTests : public ::testing::Test
	{
	protected:

		FileFinder FileFinder;

	};

	TEST_F(FileFinderTests, PrintDebugInfoTest)
	{
		FileFinder.PrintDebugInfo();
	}

	TEST_F(FileFinderTests, CurrentPathTest)
	{
		FileFinder::Path Path = FileFinder.CurrentPath();
		ASSERT_FALSE(Path.empty());
	}

	TEST_F(FileFinderTests, EngineRootPathTest)
	{
		FileFinder::Path Path = FileFinder.EngineRootPath();
		ASSERT_FALSE(Path.empty());
	}

	TEST_F(FileFinderTests, CurrentProjectRootPathTest)
	{
		FileFinder::Path Path = FileFinder.CurrentProjectRootPath();
		ASSERT_FALSE(Path.empty());
	}

	TEST_F(FileFinderTests, FindFilesInSpecificFolderTest)
	{
		FileFinder::Path FolderName = "file_finder_test_folder";
		FileFinder::Path Path = FileFinder.CurrentProjectRootPath();
		Path /= FolderName;
		FileFinder::FolderInfo Files = FileFinder.FindFiles(Path);

		size_t ExpectedFilesCount = 3u;
		size_t ActualFilesCount = Files.size();
		ASSERT_EQ(ActualFilesCount, ExpectedFilesCount);
	}

	TEST_F(FileFinderTests, FindFilesInSpecificFolderWithSpecificExtensionTest)
	{
		FileFinder::Path FolderName = "file_finder_test_folder";
		FileFinder::Path Path = FileFinder.CurrentProjectRootPath();
		Path /= FolderName;
		FileFinder::Extension Extension = ".txt2";

		FileFinder::FolderInfo Files = FileFinder.FindFiles(Path, Extension);
		size_t ExpectedFilesCount = 2u;
		size_t ActualFilesCount = Files.size();
		ASSERT_EQ(ActualFilesCount, ExpectedFilesCount);
	}

}