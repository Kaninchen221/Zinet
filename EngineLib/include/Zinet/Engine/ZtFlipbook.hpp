#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/GraphicLayer/ZtGlFlipbook.h"

namespace zt::engine
{
	class RendererContext;

	class ZINET_ENGINE_API Flipbook : public gl::Flipbook
	{

	public:

		Flipbook() = default;
		Flipbook(const Flipbook& other) = default;
		Flipbook(Flipbook&& other) = default;

		Flipbook& operator = (const Flipbook& other) = default;
		Flipbook& operator = (Flipbook&& other) = default;

		~Flipbook() noexcept = default;

	protected:

	};

}