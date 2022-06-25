#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLDeviceMemory.h"

namespace zt::gl
{
	void Buffer::create(Device& device, const vk::BufferCreateInfo& createInfo)
	{
		internal = vk::raii::Buffer{ device.getInternal(), createInfo };
		size = createInfo.size;
	}

	uint32_t Buffer::findSuitableMemoryType(
		const vk::MemoryRequirements& memoryRequirements,
		const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
		const vk::MemoryPropertyFlags& memoryPropertyFlags) const
	{
		//for (uint32_t index = 0; index < physicalDeviceMemoryProperties.memoryTypeCount; index++)
		//{
		//	if ((physicalDeviceMemoryProperties.memoryTypes[index].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
		//	{
		//		return index;
		//	}
		//}

		for (std::uint32_t index = 0; index < physicalDeviceMemoryProperties.memoryTypeCount; index++) {
			if ((memoryRequirements.memoryTypeBits & (1 << index)) &&
				(physicalDeviceMemoryProperties.memoryTypes[index].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
			{
				return index;
			}
		}

		//for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		//	if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
		//		return i;
		//	}
		//}

		Logger->error("Can't find suitable memory type");
		return UINT32_MAX;
	}

	vk::MemoryAllocateInfo Buffer::createMemoryAllocateInfo(
		const vk::MemoryRequirements& memoryRequirements,
		const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
		const vk::MemoryPropertyFlags& memoryPropertyFlags) const
	{
		vk::MemoryAllocateInfo memoryAllocateInfo{};
		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = findSuitableMemoryType(memoryRequirements, physicalDeviceMemoryProperties, memoryPropertyFlags);

		return memoryAllocateInfo;
	}

	void Buffer::bindMemory(DeviceMemory& deviceMemory)
	{
		vk::DeviceSize offset = 0;
		internal.bindMemory(*deviceMemory.getInternal(), offset);
	}

	std::uint64_t Buffer::getSize() const
	{
		return size;
	}
}