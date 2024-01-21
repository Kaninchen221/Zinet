#pragma once

#include "Zinet/Engine/Assets/ZtAssetTexture.hpp"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class AssetTextureSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<Asset, AssetTexture>);
		static_assert(std::is_default_constructible_v<AssetTexture>);
		static_assert(std::is_copy_constructible_v<AssetTexture>);
		static_assert(std::is_copy_assignable_v<AssetTexture>);
		static_assert(std::is_move_constructible_v<AssetTexture>);
		static_assert(std::is_move_assignable_v<AssetTexture>);
		static_assert(std::is_destructible_v<AssetTexture>);

		AssetTexture textureAsset;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(AssetTextureSimpleTests, Pass)
	{
	}
}