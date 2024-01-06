#include "Zinet/GraphicLayer/Buffers/ZtGLStorageBuffer.hpp"

namespace zt::gl
{

	vk::BufferCreateInfo StorageBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eStorageBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	vk::DescriptorBufferInfo StorageBuffer::createDescriptorBufferInfo() const
	{
		vk::DescriptorBufferInfo descriptorBufferInfo{};
		descriptorBufferInfo.buffer = *getInternal();
		descriptorBufferInfo.offset = 0;
		descriptorBufferInfo.range = getSize();

		return descriptorBufferInfo;
	}

}