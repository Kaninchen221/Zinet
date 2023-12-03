#pragma once

#include "Zinet/Engine/Assets/ZtAsset.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class AssetSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_default_constructible_v<Asset>);
		static_assert(std::is_copy_constructible_v<Asset>);
		static_assert(std::is_copy_assignable_v<Asset>);
		static_assert(std::is_move_constructible_v<Asset>);
		static_assert(std::is_move_assignable_v<Asset>);
		static_assert(std::is_destructible_v<Asset>);

		Asset asset;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(AssetSimpleTests, GetAny)
	{
		const std::any& any = asset.getAny();
		ASSERT_FALSE(any.has_value());
	}

	TEST_F(AssetSimpleTests, Create)
	{
		asset.create<int>();
	}

	TEST_F(AssetSimpleTests, Get_ThrowBadCast)
	{
		ASSERT_THROW(asset.get<int>(), std::bad_cast);
	}

	TEST_F(AssetSimpleTests, Get)
	{
		asset.create<int>();
		[[maybe_unused]] const int& i = asset.get<int>();
	}

	TEST_F(AssetSimpleTests, IsValid)
	{
		ASSERT_FALSE(asset.isValid());

		asset.create<int>();
		ASSERT_TRUE(asset.isValid());
	}

	TEST_F(AssetSimpleTests, Is)
	{
		ASSERT_FALSE(asset.is<int>());

		asset.create<int>();
		ASSERT_TRUE(asset.is<int>());
		ASSERT_FALSE(asset.is<double>());
	}

	TEST_F(AssetSimpleTests, Destroy)
	{
		ASSERT_FALSE(asset.isValid());

		asset.create<int>();
		ASSERT_TRUE(asset.isValid());

		asset.destroy();
		ASSERT_FALSE(asset.isValid());
	}
}