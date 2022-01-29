#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

}