#include "Zinet/GraphicLayer/ZtGLSwapChain.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLFence.h"

namespace zt::gl
{

	void SwapChain::create(
		Device& device,
		const vk::SwapchainCreateInfoKHR& createInfo
	)
	{
		vk::raii::SwapchainKHR tempSwapChain(device.getInternal(), createInfo);
		internal.swap(tempSwapChain);
		tempSwapChain.release();
	}

	vk::SwapchainCreateInfoKHR SwapChain::createCreateInfo(
		const SwapChainSupportDetails& swapChainSupportDetails,
		Surface& surface,
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
		swapChainCreateInfo.surface = *surface.getInternal();
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

	std::vector<vk::Image> SwapChain::getImages()
	{
		return internal.getImages();
		//std::vector<VkImage> rawImages = internal.getImages();
		//std::vector<vk::Image> result;
		//result.reserve(rawImages.size());
		//
		//for (VkImage& rawImage : rawImages)
		//{
		//	result.push_back({ rawImage });
		//}
		//
		//return result;
	}

	std::pair<vk::Result, uint32_t> SwapChain::acquireNextImage(uint64_t timeout, Semaphore& semaphore, Fence& fence)
	{
		std::pair<vk::Result, uint32_t> result = internal.acquireNextImage(timeout, *semaphore.getInternal(), *fence.getInternal());
		return result;
	}

}