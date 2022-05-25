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

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("SwapChain");

	public:

		SwapChain();
		SwapChain(const SwapChain& other) = default;
		SwapChain(SwapChain&& other) = default;

		SwapChain& operator = (const SwapChain& other) = default;
		SwapChain& operator = (SwapChain&& other) = default;

		~SwapChain() noexcept = default;

		// TODO Instead of the params pass one createInfo
		void create(
			Device& device,
			const SwapChainSupportDetails& swapChainSupportDetails,
			Surface& surface,
			Window& window
		);

		// TODO Rename to createCreateInfo
		vk::SwapchainCreateInfoKHR createSwapChainCreateInfo(
			const SwapChainSupportDetails& swapChainSupportDetails,
			Surface& surface,
			Window& window
		) const;

		std::vector<vk::Image> getImages();

		std::pair<vk::Result, uint32_t> acquireNextImage(uint64_t timeout, Semaphore& semaphore, Fence& fence);

	};

}