#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/GraphicLayer/ZtGlSprite.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::engine
{
	class RendererContext;

	class ZINET_ENGINE_API Sprite : public gl::Sprite
	{

	public:

		Sprite() = default;
		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		Sprite& operator = (const Sprite& other) = default;
		Sprite& operator = (Sprite&& other) = default;

		~Sprite() noexcept = default;

	protected:

	};

}