#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class VertexBuffer;

	class ZINET_GRAPHIC_LAYER_API DeviceMemory : public VulkanObject<vk::raii::DeviceMemory>
	{

	public:

		DeviceMemory() = default;
		DeviceMemory(const DeviceMemory& other) = default;
		DeviceMemory(DeviceMemory&& other) = default;

		DeviceMemory& operator = (const DeviceMemory& other) = default;
		DeviceMemory& operator = (DeviceMemory&& other) = default;

		~DeviceMemory() noexcept = default;

		void create(Device& device, const vk::MemoryAllocateInfo& memoryAllocateInfo);

		void fillWithVertexBuffer(const VertexBuffer& vertexBuffer);
	};

}