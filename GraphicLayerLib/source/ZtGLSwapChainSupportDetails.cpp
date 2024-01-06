#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.hpp"

#include "Zinet/Window/ZtWindow.hpp"

#include <cstdint>
#include <algorithm>

namespace zt::gl
{

	vk::SurfaceFormatKHR SwapChainSupportDetails::pickFormat() const
	{
		for (const vk::SurfaceFormatKHR& surfaceFormat : surfaceFormats)
		{
			if (surfaceFormat.format == vk::Format::eB8G8R8A8Srgb &&
				surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				return surfaceFormat;
			}
		}

		return vk::SurfaceFormatKHR();
	}

	vk::PresentModeKHR SwapChainSupportDetails::pickPresentMode() const
	{
		for (const vk::PresentModeKHR& presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eMailbox)
			{
				return vk::PresentModeKHR::eMailbox;
			}
		}

		return vk::PresentModeKHR::eFifo;
	}

	vk::Extent2D SwapChainSupportDetails::pickSwapExtent(wd::Window& window) const
	{
		if (surfaceCapabilities.currentExtent.width != UINT32_MAX)
		{
			return surfaceCapabilities.currentExtent;
		}
		else 
		{
			int width;
			int height;
			glfwGetFramebufferSize(window.getInternal(), &width, &height);

			VkExtent2D extent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			extent.width = std::clamp(extent.width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
			extent.height = std::clamp(extent.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);

			return extent;
		}
	}

}