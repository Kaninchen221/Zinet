#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	struct SwapChainSupportDetails;
	class Surface;
	class Window;
	class Device;

	class ZINET_GRAPHIC_LAYER_API SwapChain
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

		const vk::raii::SwapchainKHR& getInternal() const;

		void create(
			const Device& device,
			const SwapChainSupportDetails& swapChainSupportDetails,
			const Surface& surface,
			Window& window
		);

		vk::SwapchainCreateInfoKHR createSwapChainCreateInfo(
			const SwapChainSupportDetails& swapChainSupportDetails,
			const Surface& surface,
			Window& window
		) const;

	protected:

		vk::raii::SwapchainKHR internal;

	};

}