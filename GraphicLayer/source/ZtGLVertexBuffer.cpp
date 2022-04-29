#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

namespace zt::gl
{
	const std::vector<Vertex>& VertexBuffer::getVertices() const
	{
		return vertices;
	}

	void VertexBuffer::setVertices(const std::vector<Vertex>& vertices)
	{
		this->vertices = vertices;
	}

	vk::BufferCreateInfo VertexBuffer::createCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = sizeof(vertices[0]) * vertices.size();
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}
}