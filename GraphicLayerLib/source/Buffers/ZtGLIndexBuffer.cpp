#include "Zinet/GraphicLayer/Buffers/ZtGLIndexBuffer.h"

namespace zt::gl
{

	vk::BufferCreateInfo IndexBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eIndexBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;
		
		return bufferCreateInfo;
	}

}