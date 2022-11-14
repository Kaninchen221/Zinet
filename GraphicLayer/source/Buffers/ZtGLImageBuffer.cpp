#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.h"

#include "Zinet/GraphicLayer/ZtGLSampler.h"
#include "Zinet/GraphicLayer/ZtGLImageView.h"

namespace zt::gl
{
	vk::BufferCreateInfo ImageBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	vk::DescriptorImageInfo ImageBuffer::createDescriptorImageInfo(Sampler& sampler, ImageView& imageView, vk::ImageLayout imageLayout)
	{
		vk::DescriptorImageInfo descriptorImageInfo;
		descriptorImageInfo.sampler = *sampler.getInternal();
		descriptorImageInfo.imageView = *imageView.getInternal();
		descriptorImageInfo.imageLayout = imageLayout;

		return descriptorImageInfo;
	}
}