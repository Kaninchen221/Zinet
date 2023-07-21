#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include <vulkan/vulkan_enums.hpp>

namespace zt::gl
{
	bool DepthBuffer::findDepthFormat(const PhysicalDevice& physicalDevice, vk::Format& supportedFormat) const
	{
		std::vector<vk::Format> candidates = { vk::Format::eD32Sfloat, vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint };
		vk::ImageTiling imageTiling = vk::ImageTiling::eOptimal;
		vk::FormatFeatureFlags formatFeatureFlags = vk::FormatFeatureFlagBits::eDepthStencilAttachment;

		PhysicalDevice::FindSupportedFormatInput input
		{
			.candidates = candidates,
			.imageTiling = imageTiling,
			.formatFeatureFlags = formatFeatureFlags
		};

		bool supportAnyFormat = physicalDevice.findSupportedFormat(input, supportedFormat);

		return supportAnyFormat;
	}

	void DepthBuffer::create(const RendererContext& rendererContext, vk::Format format)
	{
		vk::Extent2D extent = rendererContext.getSwapExtent();
		std::uint32_t mipmapLevels = 1u;
		vk::ImageCreateInfo vkImageCreateInfo = image.createCreateInfo(extent.width, extent.height, mipmapLevels, format);
		vkImageCreateInfo.tiling = vk::ImageTiling::eOptimal;
		vkImageCreateInfo.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment;

		Image::CreateInfo imageCreateInfo
		{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = vkImageCreateInfo,
			.allocationCreateInfo = image.createAllocationCreateInfo()
		};
		image.create(imageCreateInfo);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, format);
		imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
		imageView.create(rendererContext.getDevice(), imageViewCreateInfo);
	}

	void DepthBuffer::clear()
	{
		imageView.clear();
		image.clear();
	}

}