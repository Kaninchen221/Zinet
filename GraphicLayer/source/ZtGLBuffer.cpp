#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

namespace zt::gl
{
	void Buffer::create(Device& device, const vk::BufferCreateInfo& createInfo)
	{
		internal = vk::raii::Buffer{ device.getInternal(), createInfo };
	}

	uint32_t Buffer::findSuitableMemoryType(
		const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
		const vk::MemoryPropertyFlags& memoryPropertyFlags) const
	{
		for (uint32_t index = 0; index < physicalDeviceMemoryProperties.memoryTypeCount; index++)
		{
			if ((physicalDeviceMemoryProperties.memoryTypes[index].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
			{
				return index;
			}
		}

		Logger->error("Can't find suitable memory type");
		return UINT32_MAX;
	}

	vk::MemoryAllocateInfo Buffer::createMemoryAllocateInfo(
		const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
		const vk::MemoryPropertyFlags& memoryPropertyFlags) const
	{
		vk::MemoryRequirements memoryRequirements = internal.getMemoryRequirements();

		vk::MemoryAllocateInfo memoryAllocateInfo{};
		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = findSuitableMemoryType(physicalDeviceMemoryProperties, memoryPropertyFlags);

		return memoryAllocateInfo;
	}

	void Buffer::bindMemory(DeviceMemory& deviceMemory)
	{
		vk::DeviceSize offset = 0;
		internal.bindMemory(*deviceMemory.getInternal(), offset);
	}

	void Buffer::setSize(std::uint64_t size)
	{
		this->size = size;
	}

	std::uint64_t Buffer::getSize() const
	{
		return size;
	}
}