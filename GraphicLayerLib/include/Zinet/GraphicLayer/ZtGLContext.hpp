#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Context
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Context");

	public:

		Context() = default;
		Context(const Context& other) = default;
		Context(Context&& other) = default;

		Context& operator = (const Context& other) = default;
		Context& operator = (Context&& other) = default;

		~Context() noexcept = default;

		vk::raii::Context& getInternal() { return internal; }

		vk::raii::Context* operator->() { return &internal; }

	protected:

		vk::raii::Context internal;

	};

}