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

	vk::BufferCreateInfo VertexBuffer::createVertexBufferCreateInfo() const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = sizeof(vertices[0]) * vertices.size();
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	void VertexBuffer::create(Device& device, const vk::BufferCreateInfo& vertexBufferCreateInfo)
	{
		internal = vk::raii::Buffer{ device.getInternal(), vertexBufferCreateInfo };
	}

	uint32_t VertexBuffer::findSuitableMemoryType(const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties) const
	{
		vk::MemoryRequirements memoryRequirements = internal.getMemoryRequirements();
		vk::MemoryPropertyFlags memoryPropertyFlags = vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent;

		for (uint32_t index = 0; index < physicalDeviceMemoryProperties.memoryTypeCount; index++)
		{
			if ((memoryRequirements.memoryTypeBits & (1 << index)) && (physicalDeviceMemoryProperties.memoryTypes[index].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
			{
				return index;
			}
		}

		return UINT32_MAX;
	}
	vk::MemoryAllocateInfo VertexBuffer::createMemoryAllocateInfo(const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties) const
	{
		vk::MemoryRequirements memoryRequirements = internal.getMemoryRequirements();

		vk::MemoryAllocateInfo memoryAllocateInfo{};
		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = findSuitableMemoryType(physicalDeviceMemoryProperties);

		return memoryAllocateInfo;
	}

	void VertexBuffer::bindMemory(DeviceMemory& deviceMemory)
	{
		vk::DeviceSize offset = 0;
		internal.bindMemory(*deviceMemory.getInternal(), offset);
	}
}