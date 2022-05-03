#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

namespace zt::gl
{

	vk::BufferCreateInfo VertexBuffer::createCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

}