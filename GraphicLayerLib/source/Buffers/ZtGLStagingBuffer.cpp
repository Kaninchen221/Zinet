#include "Zinet/GraphicLayer/Buffers/ZtGLStagingBuffer.hpp"

namespace zt::gl
{
	vk::BufferCreateInfo StagingBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}
}