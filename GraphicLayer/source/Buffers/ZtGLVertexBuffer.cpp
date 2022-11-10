#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	vk::BufferCreateInfo VertexBuffer::createCreateInfo(std::uint64_t size) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

}