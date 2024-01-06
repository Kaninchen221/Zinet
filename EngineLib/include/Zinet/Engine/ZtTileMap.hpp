#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/GraphicLayer/ZtGLTileMap.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include "Zinet/Math/ZtVecTypes.hpp"

namespace zt::engine
{
	class RendererContext;

	class ZINET_ENGINE_API TileMap : public gl::TileMap
	{

	public:

		struct SetTilesInput
		{
			std::vector<size_t> tilesIndices;
			Vector2ui tilesetSize;
			Vector2ui tileSize;
		};

	public:

		TileMap() = default;
		TileMap(const TileMap& other) = default;
		TileMap(TileMap&& other) = default;

		TileMap& operator = (const TileMap& other) = default;
		TileMap& operator = (TileMap&& other) = default;

		~TileMap() noexcept = default;

		void setTiles(const SetTilesInput& input);

	protected:

	};

}