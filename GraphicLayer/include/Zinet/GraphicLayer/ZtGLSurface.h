#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Instance;

	class ZINET_GRAPHIC_LAYER_API Surface : public VulkanObject<vk::raii::SurfaceKHR>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Surface");

	public:

		Surface();
		Surface(const Surface& other) = default;
		Surface(Surface&& other) = default;

		Surface& operator = (const Surface& other) = default;
		Surface& operator = (Surface&& other) = default;

		~Surface() noexcept = default;

		bool create(Instance& instance, Window& window);

	};

}