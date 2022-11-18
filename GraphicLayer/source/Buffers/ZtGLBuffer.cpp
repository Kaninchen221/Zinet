#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	Buffer::~Buffer()
	{
		if (allocation != nullptr)
		{
			vmaDestroyBuffer(vmaAllocator, nullptr, allocation);
		}
	}

	std::uint64_t Buffer::getSize() const
	{
		return size;
	}

	std::pair<void*, std::uint64_t> Buffer::getData()
	{
		std::pair<void*, std::uint64_t> result{};

		result.first = std::malloc(size);
		result.second = size;

		void* mappedData;
		vmaMapMemory(vmaAllocator, allocation, &mappedData);
		std::memcpy(result.first, mappedData, size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);

		return result;
	}

	void Buffer::fillWithCArray(void* firstElement)
	{
		void* mappedData;
		vmaMapMemory(vmaAllocator, allocation, &mappedData);
		std::memcpy(mappedData, firstElement, size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);
	}

	void Buffer::create(const BufferCreateInfo& bufferCreateInfo)
	{
		VkBuffer buffer;
		vmaAllocator = bufferCreateInfo.vma.getInternal();

		VkResult result = vmaCreateBuffer(vmaAllocator,
			&bufferCreateInfo.vkBufferCreateInfo, 
			&bufferCreateInfo.allocationCreateInfo, 
			&buffer, 
			&allocation, 
			nullptr);

		if (result == VK_SUCCESS)
		{
			size = bufferCreateInfo.vkBufferCreateInfo.size;
			internal = vk::raii::Buffer{ bufferCreateInfo.device.getInternal(), buffer };
		}
		else
		{
			Logger->error("Failed to create Buffer");
			Ensure(false);
		}

	}

	VmaAllocationCreateInfo Buffer::createVmaAllocationCreateInfo(bool randomAccess) const
	{
		VmaAllocationCreateInfo allocationCreateInfo{};
		//allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;

		if (randomAccess)
		{
			allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
		}
		else
		{
			allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
		}
		
		return allocationCreateInfo;
	}
}