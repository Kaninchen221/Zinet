#include "Zinet/GraphicLayer/ZtGLFramebuffer.hpp"

#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLImageView.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderPass.hpp"

namespace zt::gl
{
	vk::FramebufferCreateInfo Framebuffer::createCreateInfo(
		ImageView& imageView,
		RenderPass& renderPass,
		const vk::Extent2D& extent) const
	{
		vk::FramebufferCreateInfo createInfo{}; 
		createInfo.renderPass = *renderPass.getInternal();
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &*imageView.getInternal();
		createInfo.width = extent.width;
		createInfo.height = extent.height;
		createInfo.layers = 1;

		return createInfo;
	}

	void Framebuffer::create(
		const Device& device,
		vk::FramebufferCreateInfo& framebufferCreateInfo)
	{
		vk::raii::Framebuffer tempFramebuffer{ device.getInternal(), framebufferCreateInfo };
		internal.swap(tempFramebuffer);
		tempFramebuffer.release();
	}

}
