#include "Zinet/GraphicLayer/ZtGLStagingBuffer.h"

namespace zt::gl
{
	vk::BufferCreateInfo StagingBuffer::createCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}
}