#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"

namespace zt::gl
{

	void RenderTarget::create(const CreateInfo& createInfo)
	{
		createImage(createInfo);
		createImageView(createInfo);
		createFramebuffer(createInfo);
	}

	void RenderTarget::createImage(const CreateInfo& createInfo)
	{
		VkImageCreateInfo vkImageCreateInfo = image.createCreateInfo(createInfo.width, createInfo.height);
		VmaAllocationCreateInfo imageAllocationCreateInfo = image.createAllocationCreateInfo();
		Image::CreateInfo imageCreateInfo
		{
			.device = createInfo.device,
			.vma = createInfo.vma,
			.vkImageCreateInfo = vkImageCreateInfo,
			.allocationCreateInfo = imageAllocationCreateInfo
		};
		image.create(imageCreateInfo);
	}

	void RenderTarget::createImageView(const CreateInfo& createInfo)
	{
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), createInfo.format);
		imageView.create(createInfo.device, imageViewCreateInfo);
	}

	void RenderTarget::createFramebuffer(const CreateInfo& createInfo)
	{
		vk::Extent2D extent2D;
		extent2D.height = createInfo.height;
		extent2D.width = createInfo.width;
		vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(imageView, createInfo.renderPass, extent2D);
		framebuffer.create(createInfo.device, framebufferCreateInfo);
	}

}