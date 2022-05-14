#include "Zinet/GraphicLayer/ZtGLUniformBuffer.h"

namespace zt::gl
{

	vk::BufferCreateInfo UniformBuffer::createCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eUniformBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

}