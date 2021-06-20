#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtFileFinder.h"

class ZtFileFinderTests : public ::testing::Test 
{
protected:

	ZtFileFinder FileFinder;

};

TEST_F(ZtFileFinderTests, PrintDebugInfoTest)
{
	FileFinder.PrintDebugInfo();
}

TEST_F(ZtFileFinderTests, CurrentPathTest)
{
	ZtFileFinder::Path Path = FileFinder.CurrentPath();
	ASSERT_FALSE(Path.empty());
}

TEST_F(ZtFileFinderTests, EngineRootPathTest)
{
	ZtFileFinder::Path Path = FileFinder.EngineRootPath();
	ASSERT_FALSE(Path.empty());
}

TEST_F(ZtFileFinderTests, CurrentProjectRootPathTest)
{
	ZtFileFinder::Path Path = FileFinder.CurrentProjectRootPath();
	ASSERT_FALSE(Path.empty());
}

TEST_F(ZtFileFinderTests, FindFilesInSpecificFolderTest)
{
	ZtFileFinder::Path FolderName = "file_finder_test_folder";
	ZtFileFinder::Path Path = FileFinder.CurrentProjectRootPath();
	Path /= FolderName;
	auto Files = FileFinder.FindFiles(Path);

	size_t ExpectedFilesCount = 3u;
	size_t ActualFilesCount = Files.size();
	ASSERT_EQ(ActualFilesCount, ExpectedFilesCount);
}

TEST_F(ZtFileFinderTests, FindFilesInSpecificFolderWithSpecificExtensionTest)
{
	ZtFileFinder::Path FolderName = "file_finder_test_folder";
	ZtFileFinder::Path Path = FileFinder.CurrentProjectRootPath();
	Path /= FolderName;
	ZtFileFinder::Extension Extension = ".txt2";

	auto Files = FileFinder.FindFiles(Path, Extension);
	size_t ExpectedFilesCount = 2u;
	size_t ActualFilesCount = Files.size();
	ASSERT_EQ(ActualFilesCount, ExpectedFilesCount);
}