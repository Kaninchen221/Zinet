#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"


#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Context
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Context");

	public:

		Context() = default;
		Context(const Context& other) = default;
		Context(Context&& other) = default;

		Context& operator = (const Context& other) = default;
		Context& operator = (Context&& other) = default;

		~Context() noexcept = default;

		const vk::raii::Context& getInternal() const;

	protected:

		vk::raii::Context internal;

	};

}