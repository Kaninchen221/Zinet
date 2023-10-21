#include "Zinet/GraphicLayer/ZtGLDepthStencilBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLUtilities.h"

#include "Zinet/Math/ZtMath.h"

#include <vulkan/vulkan_enums.hpp>

namespace zt::gl
{
	bool DepthStencilBuffer::findDepthFormat(const PhysicalDevice& physicalDevice, vk::Format& supportedFormat) const
	{
		std::vector<vk::Format> candidates = { vk::Format::eD32SfloatS8Uint, vk::Format::eD24UnormS8Uint };
		vk::ImageTiling imageTiling = vk::ImageTiling::eOptimal;
		vk::FormatFeatureFlags formatFeatureFlags = vk::FormatFeatureFlagBits::eDepthStencilAttachment;

		PhysicalDevice::FindSupportedFormatInput input
		{
			.candidates = candidates,
			.imageTiling = imageTiling,
			.formatFeatureFlags = formatFeatureFlags
		};

		bool foundFormat = physicalDevice.findSupportedFormat(input, supportedFormat);
		return foundFormat;
	}

	void DepthStencilBuffer::create(RendererContext& rendererContext, vk::Format format)
	{
		vk::Extent2D extent = rendererContext.getSwapExtent();
		std::uint32_t mipmapLevels = 1u;
		vk::ImageCreateInfo vkImageCreateInfo = image.createCreateInfo(Utilities::FromExtent2DToVector2<Vector2ui>(extent), mipmapLevels, format);
		vkImageCreateInfo.tiling = vk::ImageTiling::eOptimal;
		vkImageCreateInfo.usage = vk::ImageUsageFlagBits::eDepthStencilAttachment;

		Image::CreateInfo imageCreateInfo
		{
			.device = rendererContext.getDevice(),
			.vma = rendererContext.getVma(),
			.vkImageCreateInfo = vkImageCreateInfo,
			.allocationCreateInfo = image.createAllocationCreateInfo(),
			.imageAspectFlags = vk::ImageAspectFlagBits::eDepth | vk::ImageAspectFlagBits::eStencil
		};
		image.create(imageCreateInfo);

		CommandBuffer& commandBuffer = rendererContext.getCommandBuffer();
		commandBuffer.begin();
		image.changeLayout(commandBuffer, vk::ImageLayout::eDepthStencilAttachmentOptimal, vk::PipelineStageFlagBits::eFragmentShader);
		commandBuffer.end();
		rendererContext.getQueue().submitWaitIdle(commandBuffer);

		vk::ImageViewCreateInfo imageViewCreateInfo = imageView.createCreateInfo(*image.getInternal(), mipmapLevels, format);
		imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eDepth;
		imageView.create(rendererContext.getDevice(), imageViewCreateInfo);
	}

	void DepthStencilBuffer::clear()
	{
		imageView.clear();
		image.clear();
	}

	bool DepthStencilBuffer::isValid() const
	{
		return image.isValid() && imageView.isValid();
	}

}