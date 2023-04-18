#include "Zinet/GraphicLayer/ZtGLRenderTarget.h"

namespace zt::gl
{

	void RenderTarget::create(const CreateInfo& createInfo)
	{
		createImage(createInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), createInfo.format);
		imageView.create(createInfo.device, imageViewCreateInfo);
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

}