#include "Zinet/GraphicLayer/ZtGLImageView.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	ImageView::ImageView()
	{

	}

	vk::ImageViewCreateInfo ImageView::createCreateInfo(vk::Image image, const vk::Format& format) const
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

		return imageViewCreateInfo;
	}

	void ImageView::create(Device& device, vk::Image image, const vk::Format& format)
	{
		vk::ImageViewCreateInfo imageViewCreateInfo = createCreateInfo(image, format);
		internal = std::move(vk::raii::ImageView(device.getInternal(), imageViewCreateInfo));
	}
}