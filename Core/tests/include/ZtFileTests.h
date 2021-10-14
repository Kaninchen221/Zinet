#pragma once

#include "gtest/gtest.h"

#include "Zinet/Core/ZtFile.h"

class ZtFileTests : public ::testing::Test
{
protected:

	ZtFile File;

	ZtFileFinder::Path TestFolderPath = ZtFileFinder().CurrentProjectRootPath() / "file_test_folder";
	ZtFileFinder::Path PathToReadOnlyFile = TestFolderPath / "read_only_file.txt";
};

TEST_F(ZtFileTests, OpenTest)
{
	bool IsOpen = File.IsOpen();
	ASSERT_FALSE(IsOpen);
		
	File.Open(PathToReadOnlyFile, ZtFileOpenMode::In);
	IsOpen = File.IsOpen();
	ASSERT_TRUE(IsOpen);
}

TEST_F(ZtFileTests, ReadLineTest)
{
	File.Open(PathToReadOnlyFile, ZtFileOpenMode::In);

	std::string ActualFirstLine = File.ReadLine();
	std::string ExpectedFirstLine = "test text";
	ASSERT_EQ(ActualFirstLine, ExpectedFirstLine);

	std::string ActualSecondLine = File.ReadLine();
	std::string ExpectedSecondLine = "should be never modified";
	ASSERT_EQ(ActualSecondLine, ExpectedSecondLine);
}

TEST_F(ZtFileTests, ZtFileOpenModeToStdOpenMode)
{
	std::ios_base::openmode ActualOpenMode = ZtFile::ZtFileOpenModeToStdOpenMode(ZtFileOpenMode::Truncate);
	std::ios_base::openmode ExpectedOpenMode = std::ios_base::trunc;
	ASSERT_EQ(ActualOpenMode, ExpectedOpenMode);
}

TEST_F(ZtFileTests, ReadAllTest)
{
	File.Open(PathToReadOnlyFile, ZtFileOpenMode::In);
	std::string ActualText = File.ReadAll();
	std::string ExpectedText = "test text\nshould be never modified\n";
	ASSERT_EQ(ActualText, ExpectedText);

}