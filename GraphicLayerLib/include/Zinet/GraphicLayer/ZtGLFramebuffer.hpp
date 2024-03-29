#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Device;
	class ImageView;
	class RenderPass;

	class ZINET_GRAPHIC_LAYER_API Framebuffer : public VulkanObject<vk::raii::Framebuffer>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Framebuffer");

	public:

		Framebuffer() = default;
		Framebuffer(const Framebuffer& other) = default;
		Framebuffer(Framebuffer&& other) = default;

		Framebuffer& operator = (const Framebuffer& other) = default;
		Framebuffer& operator = (Framebuffer&& other) = default;

		~Framebuffer() noexcept = default;

		vk::FramebufferCreateInfo createCreateInfo(
			ImageView& imageView,
			RenderPass& renderPass,
			const vk::Extent2D& extent) const;

		void create(const Device& device, vk::FramebufferCreateInfo& framebufferCreateInfo);

	};

}
