#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	vk::ImageViewCreateInfo ImageView::createCreateInfo(vk::Image image, std::uint32_t newMipmapLevels, const vk::Format& format) const
	{
		vk::ImageViewCreateInfo imageViewCreateInfo;
		imageViewCreateInfo.image = image; 
		imageViewCreateInfo.viewType = vk::ImageViewType::e2D;
		imageViewCreateInfo.format = format;
		imageViewCreateInfo.components.r = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.g = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.b = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.a = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;
		imageViewCreateInfo.subresourceRange.levelCount = newMipmapLevels;

		return imageViewCreateInfo;
	}

	void ImageView::create(const Device& device, const vk::ImageViewCreateInfo& imageViewCreateInfo)
	{
		vk::raii::ImageView tempImageView(device.getInternal(), imageViewCreateInfo);
		internal.swap(tempImageView);
		tempImageView.release();

		if (isValid())
		{
			mipmapLevels = imageViewCreateInfo.subresourceRange.levelCount;
		}
	}
}