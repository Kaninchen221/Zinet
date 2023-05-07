#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class ImageView;
	class RenderPass;

	class ZINET_GRAPHIC_LAYER_API Framebuffer : public VulkanObject<vk::raii::Framebuffer>
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Framebuffer");

	public:

		Framebuffer();
		Framebuffer(const Framebuffer& other) = default;
		Framebuffer(Framebuffer&& other) = default;

		Framebuffer& operator = (const Framebuffer& other) = default;
		Framebuffer& operator = (Framebuffer&& other) = default;

		~Framebuffer() noexcept = default;

		vk::FramebufferCreateInfo createCreateInfo(
			ImageView& imageView,
			RenderPass& renderPass,
			const vk::Extent2D& swapChainExtent) const;

		void create(const Device& device, vk::FramebufferCreateInfo& framebufferCreateInfo);

	};

}
