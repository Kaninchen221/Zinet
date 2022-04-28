#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include <vector>

namespace zt::gl
{
	class Vertex;
	class Device;
	class DeviceMemory;

	class ZINET_GRAPHIC_LAYER_API VertexBuffer : public VulkanObject<vk::raii::Buffer>
	{

	public:

		VertexBuffer() = default;
		VertexBuffer(const VertexBuffer& other) = default;
		VertexBuffer(VertexBuffer&& other) = default;

		VertexBuffer& operator = (const VertexBuffer& other) = default;
		VertexBuffer& operator = (VertexBuffer&& other) = default;

		~VertexBuffer() noexcept = default;

		const std::vector<Vertex>& getVertices() const;

		void setVertices(const std::vector<Vertex>& vertices);

		vk::BufferCreateInfo createVertexBufferCreateInfo() const;

		void create(Device& device, const vk::BufferCreateInfo& vertexBufferCreateInfo);

		uint32_t findSuitableMemoryType(const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, const vk::MemoryPropertyFlags& memoryPropertyFlags) const;

		vk::MemoryAllocateInfo createMemoryAllocateInfo(const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, const vk::MemoryPropertyFlags& memoryPropertyFlags) const;

		void bindMemory(DeviceMemory& deviceMemory);

	protected:

		std::vector<Vertex> vertices;

	};

}