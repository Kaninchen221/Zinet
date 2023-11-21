#pragma once

#include "Zinet/Engine/ZtTileMap.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class TileMapSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_base_of_v<gl::TileMap, engine::TileMap>);
		static_assert(std::is_default_constructible_v<TileMap>);
		static_assert(std::is_copy_constructible_v<TileMap>);
		static_assert(std::is_copy_assignable_v<TileMap>);
		static_assert(std::is_move_constructible_v<TileMap>);
		static_assert(std::is_move_assignable_v<TileMap>);
		static_assert(std::is_destructible_v<TileMap>);

		TileMap tileMap;

		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(TileMapSimpleTests, SetTiles)
	{
		TileMap::SetTilesInput setTilesInput
		{
			.tilesIndices = std::vector<size_t>{},
			.tilesetSize = Vector2ui{},
			.tileSize = Vector2ui{}
		};

		tileMap.setTiles(setTilesInput);
	}

}