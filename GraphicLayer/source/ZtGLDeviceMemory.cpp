#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLVertex.h"
#include "Zinet/GraphicLayer/Buffers/ZtGLVertexBuffer.h"

namespace zt::gl
{
	void DeviceMemory::create(Device& device, const vk::MemoryAllocateInfo& memoryAllocateInfo)
	{
		internal = vk::raii::DeviceMemory{ device.getInternal(), memoryAllocateInfo };
	}

	void DeviceMemory::fillWithArray(const void* const array, std::size_t size)
	{
		vk::DeviceSize offset = 0u;
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, array, size);

		internal.unmapMemory();
	}

	std::pair<void*, std::uint64_t> DeviceMemory::getData(vk::DeviceSize size) const
	{
		std::pair<void*, std::uint64_t> result{}; 

		result.first = std::malloc(size);
		result.second = size;

		vk::DeviceSize offset = 0u;
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(result.first, memory, size);

		internal.unmapMemory();

		return result;
	}
}