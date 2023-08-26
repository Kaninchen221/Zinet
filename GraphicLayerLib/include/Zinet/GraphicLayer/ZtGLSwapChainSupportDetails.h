#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

namespace zt::gl
{
	class Window;

	struct ZINET_GRAPHIC_LAYER_API SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR surfaceCapabilities;
		std::vector<vk::SurfaceFormatKHR> surfaceFormats;
		std::vector<vk::PresentModeKHR> presentModes;

		vk::SurfaceFormatKHR pickFormat() const;

		vk::PresentModeKHR pickPresentMode() const;

		vk::Extent2D pickSwapExtent(Window& window) const;

	};

}