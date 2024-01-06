#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::wd
{
	class Window;
}

namespace zt::gl
{
	struct SwapChainSupportDetails;
	class Surface;
	class Device;
	class Semaphore;
	class Fence;

	class ZINET_GRAPHIC_LAYER_API SwapChain : public VulkanObject<vk::raii::SwapchainKHR>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("SwapChain");

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
			wd::Window& window
		) const;

		// Images (acquired from the swapchain) lifetime are controlled by the implementation
		std::vector<vk::Image> getImages();

		std::pair<vk::Result, uint32_t> acquireNextImage(uint64_t timeout, Semaphore& semaphore, Fence& fence);

	};

}