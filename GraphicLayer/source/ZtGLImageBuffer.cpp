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
}