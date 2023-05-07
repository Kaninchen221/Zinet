#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	struct SwapChainSupportDetails;
	class Surface;
	class Window;
	class Device;
	class Semaphore;
	class Fence;

	class ZINET_GRAPHIC_LAYER_API SwapChain : public VulkanObject<vk::raii::SwapchainKHR>
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("SwapChain");

	public:

		SwapChain() = default;
		SwapChain(const SwapChain& other) = default;
		SwapChain(SwapChain&& other) = default;

		SwapChain& operator = (const SwapChain& other) = default;
		SwapChain& operator = (SwapChain&& other) = default;

		~SwapChain() noexcept = default;

		void create(Device& device, const vk::SwapchainCreateInfoKHR& createInfo);

		vk::SwapchainCreateInfoKHR createCreateInfo(
			const SwapChainSupportDetails& swapChainSupportDetails,
			Surface& surface,
			Window& window
		) const;

		// Images (acquired from the swapchain) lifetime are controlled by the implementation
		std::vector<vk::Image> getImages();

		std::pair<vk::Result, uint32_t> acquireNextImage(uint64_t timeout, Semaphore& semaphore, Fence& fence);

	};

}