#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

#include "Zinet/Window/ZtWindow.hpp"

namespace zt::gl
{
	class Instance;

	class ZINET_GRAPHIC_LAYER_API Surface : public VulkanObject<vk::raii::SurfaceKHR>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Surface");

	public:

		Surface() = default;
		Surface(const Surface& other) = default;
		Surface(Surface&& other) = default;

		Surface& operator = (const Surface& other) = default;
		Surface& operator = (Surface&& other) = default;

		~Surface() noexcept = default;

		bool create(Instance& instance, wd::Window& window);

	};

}