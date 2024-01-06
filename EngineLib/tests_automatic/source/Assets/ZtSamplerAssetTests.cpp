#pragma once

#include "Zinet/Engine/Assets/ZtSamplerAsset.hpp"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class SamplerAssetSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<Asset, SamplerAsset>);
		static_assert(std::is_default_constructible_v<SamplerAsset>);
		static_assert(std::is_copy_constructible_v<SamplerAsset>);
		static_assert(std::is_copy_assignable_v<SamplerAsset>);
		static_assert(std::is_move_constructible_v<SamplerAsset>);
		static_assert(std::is_move_assignable_v<SamplerAsset>);
		static_assert(std::is_destructible_v<SamplerAsset>);

		SamplerAsset samplerAsset;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(SamplerAssetSimpleTests, Pass)
	{
	}
}