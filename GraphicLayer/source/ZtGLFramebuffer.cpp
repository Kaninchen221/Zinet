#include "Zinet/GraphicLayer/ZtGLFramebuffer.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"
#include "Zinet/GraphicLayer/ZtGLRenderPass.h"

namespace zt::gl
{
	Framebuffer::Framebuffer()
	{
	}

	vk::FramebufferCreateInfo Framebuffer::createFramebufferCreateInfo(
		ImageView& imageView,
		RenderPass& renderPass,
		const vk::Extent2D& swapChainExtent) const
	{
		vk::FramebufferCreateInfo createInfo{}; 
		createInfo.renderPass = *renderPass.getInternal();
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &*imageView.getInternal();
		createInfo.width = swapChainExtent.width;
		createInfo.height = swapChainExtent.height;
		createInfo.layers = 1;

		return createInfo;
	}

	void Framebuffer::create(
		Device& device,
		ImageView& imageView, 
		RenderPass& renderPass, 
		const vk::Extent2D& swapChainExtent)
	{
		vk::FramebufferCreateInfo createInfo = createFramebufferCreateInfo(imageView, renderPass, swapChainExtent);
		internal = std::move(vk::raii::Framebuffer{ device.getInternal(), createInfo });
	}

}
