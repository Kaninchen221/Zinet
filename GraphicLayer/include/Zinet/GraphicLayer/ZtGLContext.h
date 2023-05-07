#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Context
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Context");

	public:

		Context() = default;
		Context(const Context& other) = default;
		Context(Context&& other) = default;

		Context& operator = (const Context& other) = default;
		Context& operator = (Context&& other) = default;

		~Context() noexcept = default;

		vk::raii::Context& getInternal();

		vk::raii::Context* operator->();

	protected:

		vk::raii::Context internal;

	};

}