#include "Zinet/GraphicLayer/ZtGLIndexBuffer.h"

namespace zt::gl
{

	vk::BufferCreateInfo IndexBuffer::createCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;
		
		return bufferCreateInfo;
	}

}