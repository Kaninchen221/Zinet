#include "Zinet/GraphicLayer/Buffers/ZtGLImageBuffer.hpp"

#include "Zinet/GraphicLayer/ZtGLSampler.hpp"
#include "Zinet/GraphicLayer/ZtGLImageView.hpp"

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

	vk::DescriptorImageInfo ImageBuffer::createDescriptorImageInfo(const Sampler& sampler, const ImageView& imageView, vk::ImageLayout imageLayout) const
	{
		vk::DescriptorImageInfo descriptorImageInfo;
		descriptorImageInfo.sampler = *sampler.getInternal();
		descriptorImageInfo.imageView = *imageView.getInternal();
		descriptorImageInfo.imageLayout = imageLayout;

		return descriptorImageInfo;
	}
}