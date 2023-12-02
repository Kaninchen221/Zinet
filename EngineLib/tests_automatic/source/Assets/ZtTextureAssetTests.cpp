#pragma once

#include "Zinet/Engine/Assets/ZtTextureAsset.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class TextureAssetSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<Asset, TextureAsset>);
		static_assert(std::is_default_constructible_v<TextureAsset>);
		static_assert(std::is_copy_constructible_v<TextureAsset>);
		static_assert(std::is_copy_assignable_v<TextureAsset>);
		static_assert(std::is_move_constructible_v<TextureAsset>);
		static_assert(std::is_move_assignable_v<TextureAsset>);
		static_assert(std::is_destructible_v<TextureAsset>);

		TextureAsset textureAsset;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(TextureAssetSimpleTests, Pass)
	{
	}
}