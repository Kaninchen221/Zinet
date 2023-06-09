#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

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

}