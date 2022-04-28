#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"

namespace zt::gl
{
	void DeviceMemory::create(Device& device, const vk::MemoryAllocateInfo& memoryAllocateInfo)
	{
		internal = vk::raii::DeviceMemory{ device.getInternal(), memoryAllocateInfo };
	}

	void DeviceMemory::fillWithVertexBuffer(const VertexBuffer& vertexBuffer)
	{
		const std::vector<Vertex>& vertices = vertexBuffer.getVertices();

		vk::DeviceSize offset = 0u;
		vk::DeviceSize size = sizeof(Vertex) * vertices.size();
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, vertices.data(), size);

		internal.unmapMemory();
	}
}