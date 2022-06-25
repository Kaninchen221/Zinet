#include "Zinet/GraphicLayer/ZtGLImageBuffer.h"

namespace zt::gl
{
	vk::BufferCreateInfo ImageBuffer::createCreateInfo(std::uint64_t size) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	vk::DescriptorBufferInfo ImageBuffer::createDescriptorBufferInfo()
	{
		vk::DescriptorBufferInfo descriptorBufferInfo;
		descriptorBufferInfo.buffer = *getInternal();
		descriptorBufferInfo.offset = 0;
		descriptorBufferInfo.range = size;

		return descriptorBufferInfo;
	}
}