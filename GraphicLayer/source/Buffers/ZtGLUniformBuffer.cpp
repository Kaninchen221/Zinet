#include "Zinet/GraphicLayer/Buffers/ZtGLUniformBuffer.h"

namespace zt::gl
{

	vk::BufferCreateInfo UniformBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eUniformBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	vk::DescriptorBufferInfo UniformBuffer::createDescriptorBufferInfo()
	{
		vk::DescriptorBufferInfo descriptorBufferInfo;
		descriptorBufferInfo.buffer = *getInternal();
		descriptorBufferInfo.offset = 0;
		descriptorBufferInfo.range = getSize();

		return descriptorBufferInfo;
	}

}