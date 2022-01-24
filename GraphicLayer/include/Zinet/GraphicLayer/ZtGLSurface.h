#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Surface
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Surface");

	public:

		Surface() = default;
		Surface(const Surface& other) = default;
		Surface(Surface&& other) = default;

		Surface& operator = (const Surface& other) = default;
		Surface& operator = (Surface&& other) = default;

		~Surface() noexcept;

		bool create(const Instance& instance, Window& window);

		VkSurfaceKHR getInternal() const;

		void destroySurface(const Instance& instance);

	protected:

		VkSurfaceKHR internal{};

	};

}