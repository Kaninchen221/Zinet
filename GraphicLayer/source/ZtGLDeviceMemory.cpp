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
		//void* data;
		//vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
		//vkUnmapMemory(device, vertexBufferMemory);

		//mapMemory(VULKAN_HPP_NAMESPACE::DeviceSize           offset,
		//	VULKAN_HPP_NAMESPACE::DeviceSize           size,
		//	VULKAN_HPP_NAMESPACE::MemoryMapFlags flags VULKAN_HPP_DEFAULT_ARGUMENT_ASSIGNMENT) const;
		//
		//void unmapMemory() const VULKAN_HPP_NOEXCEPT;

		const std::vector<Vertex>& vertices = vertexBuffer.getVertices();

		vk::DeviceSize offset = 0u;
		vk::DeviceSize size = sizeof(Vertex) * vertices.size();
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, vertices.data(), vertices.size());

		internal.unmapMemory();
	}
}