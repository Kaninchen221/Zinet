#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/GraphicLayer/ZtGLTileMap.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::engine
{
	class RendererContext;

	class ZINET_ENGINE_API TileMap : public gl::TileMap
	{

	public:

		TileMap() = default;
		TileMap(const TileMap& other) = default;
		TileMap(TileMap&& other) = default;

		TileMap& operator = (const TileMap& other) = default;
		TileMap& operator = (TileMap&& other) = default;

		~TileMap() noexcept = default;

		void placeholder();

	protected:

	};

}