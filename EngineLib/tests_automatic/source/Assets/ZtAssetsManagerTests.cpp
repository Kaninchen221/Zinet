#pragma once

#include "Zinet/Engine/Assets/ZtAssetsManager.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class AssetsManagerSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<AssetsManager>);
		static_assert(std::is_copy_constructible_v<AssetsManager>);
		static_assert(std::is_copy_assignable_v<AssetsManager>);
		static_assert(std::is_move_constructible_v<AssetsManager>);
		static_assert(std::is_move_assignable_v<AssetsManager>);
		static_assert(std::is_destructible_v<AssetsManager>);

		AssetsManager assetsManager;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(AssetsManagerSimpleTests, AddAsset)
	{
		const std::string contentPath = "Content/Textures/Texture_1.meta";
		Asset asset;
		assetsManager.addAsset(contentPath, asset);
	}

	TEST_F(AssetsManagerSimpleTests, GetAsset_InvalidResult)
	{
		const std::string contentPath = "Content/Textures/Texture_1.meta";
		const AssetReference invalidResult = assetsManager.getAsset(contentPath);
		ASSERT_FALSE(invalidResult.success);
	}

	TEST_F(AssetsManagerSimpleTests, GetAsset_ValidResult)
	{
		const std::string contentPath = "Content/Textures/Texture_1.meta";
		Asset asset;
		assetsManager.addAsset(contentPath, asset);

		const AssetReference validResult = assetsManager.getAsset(contentPath);
		ASSERT_TRUE(validResult.success);
		EXPECT_FALSE(validResult->isValid());
	}

}