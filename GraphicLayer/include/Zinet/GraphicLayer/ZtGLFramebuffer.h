#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class ImageView;
	class RenderPass;

	class ZINET_GRAPHIC_LAYER_API Framebuffer
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Framebuffer");

	public:

		Framebuffer();
		Framebuffer(const Framebuffer& other) = default;
		Framebuffer(Framebuffer&& other) = default;

		Framebuffer& operator = (const Framebuffer& other) = default;
		Framebuffer& operator = (Framebuffer&& other) = default;

		~Framebuffer() noexcept = default;

		vk::raii::Framebuffer& getInternal();

		vk::FramebufferCreateInfo createFramebufferCreateInfo(
			ImageView& imageView,
			RenderPass& renderPass,
			const vk::Extent2D& swapChainExtent) const;

		void create(
			Device& device,
			ImageView& imageView,
			RenderPass& renderPass,
			const vk::Extent2D& swapChainExtent);

	protected:

		vk::raii::Framebuffer internal;

	};

}
