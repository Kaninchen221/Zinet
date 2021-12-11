#pragma once

#include "gtest/gtest.h"

#include "Zinet/Core/ZtFile.h"

namespace zt::tests
{

	class FileTests : public ::testing::Test
	{
	protected:

		File File;

		FileFinder::Path TestFolderPath = FileFinder().CurrentProjectRootPath() / "file_test_folder";
		FileFinder::Path PathToReadOnlyFile = TestFolderPath / "read_only_file.txt";
	};

	TEST_F(FileTests, OpenTest)
	{
		bool IsOpen = File.IsOpen();
		ASSERT_FALSE(IsOpen);

		File.Open(PathToReadOnlyFile, FileOpenMode::In);
		IsOpen = File.IsOpen();
		ASSERT_TRUE(IsOpen);
	}

	TEST_F(FileTests, ReadLineTest)
	{
		File.Open(PathToReadOnlyFile, FileOpenMode::In);

		std::string ActualFirstLine = File.ReadLine();
		std::string ExpectedFirstLine = "test text";
		ASSERT_EQ(ActualFirstLine, ExpectedFirstLine);

		std::string ActualSecondLine = File.ReadLine();
		std::string ExpectedSecondLine = "should be never modified";
		ASSERT_EQ(ActualSecondLine, ExpectedSecondLine);
	}

	TEST_F(FileTests, ZtFileOpenModeToStdOpenMode)
	{
		std::ios_base::openmode ActualOpenMode = File::ToStdOpenMode(FileOpenMode::Truncate);
		std::ios_base::openmode ExpectedOpenMode = std::ios_base::trunc;
		ASSERT_EQ(ActualOpenMode, ExpectedOpenMode);
	}

	TEST_F(FileTests, ReadAllTest)
	{
		File.Open(PathToReadOnlyFile, FileOpenMode::In);
		std::string ActualText = File.ReadAll();
		std::string ExpectedText = "test text\nshould be never modified\n";
		ASSERT_EQ(ActualText, ExpectedText);
	}

}