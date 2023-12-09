#pragma once

#include "Zinet/Engine/Assets/ZtAssetsFinder.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class AssetsFinderSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<AssetsFinder>);
		static_assert(std::is_copy_constructible_v<AssetsFinder>);
		static_assert(std::is_copy_assignable_v<AssetsFinder>);
		static_assert(std::is_move_constructible_v<AssetsFinder>);
		static_assert(std::is_move_assignable_v<AssetsFinder>);
		static_assert(std::is_destructible_v<AssetsFinder>);

		AssetsFinder assetsFinder;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(AssetsFinderSimpleTests, SetGetContentFolderPath)
	{
		const std::filesystem::path expectedPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/Assets";
		assetsFinder.setContentFolderRootPath(expectedPath);

		const std::filesystem::path& actualPath = assetsFinder.getContentFolderRootPath();
		EXPECT_EQ(expectedPath, actualPath);
	}

	TEST_F(AssetsFinderSimpleTests, AssetsMetaFilePostfix)
	{
		const std::string& defaultMetaFilePostix = assetsFinder.getAssetsMetaFilePostfix();
		const std::string expectedDefaultAssetsMetaFilePostfix = ".meta";
		EXPECT_EQ(defaultMetaFilePostix, expectedDefaultAssetsMetaFilePostfix);

		const std::string expectedAssetsMetaFilePostfix = "meta_data";
		assetsFinder.setAssetsMetaFilePostfix(expectedAssetsMetaFilePostfix);
		const std::string& actualMetaFilePostix = assetsFinder.getAssetsMetaFilePostfix();
		EXPECT_EQ(expectedAssetsMetaFilePostfix, actualMetaFilePostix);
	}

	TEST_F(AssetsFinderSimpleTests, FindAllAssetsMetaData)
	{
		const std::filesystem::path contentFolderRootPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files/Assets";
		assetsFinder.setContentFolderRootPath(contentFolderRootPath);

		const std::vector<std::filesystem::directory_entry> findAllAssetsMetaDataResult = assetsFinder.findAllAssetsMetaData();
		EXPECT_EQ(findAllAssetsMetaDataResult.size(), 2u);
	}
}