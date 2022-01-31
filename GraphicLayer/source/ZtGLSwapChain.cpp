#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

namespace zt::gl
{
	SwapChain::SwapChain()
		: internal(std::nullptr_t())
	{
	}

	const vk::raii::SwapchainKHR& SwapChain::getInternal() const
	{
		return internal;
	}

	void SwapChain::create(
		const Device& device,
		const SwapChainSupportDetails& swapChainSupportDetails,
		const Surface& surface,
		Window& window
	)
	{
		vk::SwapchainCreateInfoKHR swapChainCreateInfo = createSwapChainCreateInfo(swapChainSupportDetails, surface, window);
		internal = std::move(vk::raii::SwapchainKHR(device.getInternal(), swapChainCreateInfo));
	}

	vk::SwapchainCreateInfoKHR SwapChain::createSwapChainCreateInfo(
		const SwapChainSupportDetails& swapChainSupportDetails,
		const Surface& surface,
		Window& window
	) const
	{
		vk::SurfaceCapabilitiesKHR surfaceCapabilities = swapChainSupportDetails.surfaceCapabilities;
		vk::SurfaceFormatKHR surfaceFormat = swapChainSupportDetails.pickFormat();
		vk::PresentModeKHR presentMode = swapChainSupportDetails.pickPresentMode();
		vk::Extent2D extent = swapChainSupportDetails.pickSwapExtent(window);

		uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
		if (surfaceCapabilities.maxImageCount > 0 &&
			imageCount > surfaceCapabilities.maxImageCount)
		{
			imageCount = surfaceCapabilities.maxImageCount;
		}

		vk::SwapchainCreateInfoKHR swapChainCreateInfo;
		swapChainCreateInfo.sType = vk::StructureType::eSwapchainCreateInfoKHR;
		swapChainCreateInfo.surface = surface.getInternal();
		swapChainCreateInfo.minImageCount = imageCount;
		swapChainCreateInfo.imageFormat = surfaceFormat.format;
		swapChainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapChainCreateInfo.imageExtent = extent;
		swapChainCreateInfo.imageArrayLayers = 1;
		swapChainCreateInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
		swapChainCreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
		swapChainCreateInfo.queueFamilyIndexCount = 0;
		swapChainCreateInfo.pQueueFamilyIndices = nullptr;
		swapChainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
		swapChainCreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		swapChainCreateInfo.presentMode = presentMode;
		swapChainCreateInfo.clipped = VK_TRUE;
		swapChainCreateInfo.oldSwapchain = vk::SwapchainKHR(std::nullptr_t());

		return swapChainCreateInfo;
	}

}