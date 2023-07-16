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
		std::uint32_t mipmapLevels = 1u;
		vk::ImageCreateInfo vkImageCreateInfo = image.createCreateInfo(createInfo.width, createInfo.height, mipmapLevels, createInfo.format);
		vkImageCreateInfo.usage = vk::ImageUsageFlagBits::eColorAttachment;
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
		std::uint32_t mipmapLevels = 1u;
		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, createInfo.format);
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

	void RenderTargetDisplay::create(const CreateInfo& createInfo)
	{
		createImageView(createInfo);
		createFramebuffer(createInfo);
	}

	void RenderTargetDisplay::createImageView(const CreateInfo& createInfo)
	{
		swapChainImage = createInfo.swapChainImage;

		std::uint32_t mipmapLevels = 1u;
		vk::ImageViewCreateInfo imageViewCreateInfo = swapChainImageView.createCreateInfo(swapChainImage, mipmapLevels, createInfo.format);
		swapChainImageView.create(createInfo.device, imageViewCreateInfo);
	}

	void RenderTargetDisplay::createFramebuffer(const CreateInfo& createInfo)
	{
		std::vector<vk::ImageView> attachments;

		if (createInfo.depthBufferImageView)
			attachments = { swapChainImageView.getVk(), createInfo.depthBufferImageView };
		else
			attachments = { swapChainImageView.getVk() };

		vk::Extent2D extent{ createInfo.width, createInfo.height };
		vk::FramebufferCreateInfo framebufferCreateInfo = framebuffer.createCreateInfo(swapChainImageView, createInfo.renderPass, extent);
		framebufferCreateInfo.attachmentCount = static_cast<std::uint32_t>(attachments.size());
		framebufferCreateInfo.pAttachments = attachments.data();

		framebuffer.create(createInfo.device, framebufferCreateInfo);
	}

}