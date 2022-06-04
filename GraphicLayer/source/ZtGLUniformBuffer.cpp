#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"

namespace zt::gl
{

	vk::BufferCreateInfo UniformBuffer::createCreateInfo(std::uint64_t size) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eUniformBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	vk::DescriptorBufferInfo UniformBuffer::createDescriptorBufferInfo()
	{
		vk::DescriptorBufferInfo descriptorBufferInfo;
		descriptorBufferInfo.buffer = *getInternal();
		descriptorBufferInfo.offset = 0;
		descriptorBufferInfo.range = size;

		return descriptorBufferInfo;
	}

}