#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	vk::BufferCreateInfo VertexBuffer::createCreateInfo(std::uint64_t newSize) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = newSize;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

}