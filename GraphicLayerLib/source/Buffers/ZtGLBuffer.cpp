#include "Zinet/GraphicLayer/Buffers/ZtGLBuffer.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"

namespace zt::gl
{
	Buffer::Buffer(Buffer&& other)
	{
		*this = std::move(other);
	}

	Buffer& Buffer::operator=(Buffer&& other)
	{
		this->VulkanObject<vk::raii::Buffer>::operator=(std::move(other));
		vmaAllocator = std::move(other.vmaAllocator);
		allocation = std::move(other.allocation);
		size = std::move(other.size);
		
		other.vmaAllocator = nullptr;
		other.allocation = nullptr;
		other.size = 0u;

		return *this;
	}

	Buffer::~Buffer()
	{
		if (allocation != nullptr)
		{
			vmaDestroyBuffer(vmaAllocator, nullptr, allocation);
			allocation = nullptr;
		}
	}

	std::uint64_t Buffer::getSize() const
	{
		return size;
	}

	std::unique_ptr<void, decltype(zt::core::LambdaFree)> Buffer::getData()
	{
		void* mappedData = nullptr;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		void* data = std::malloc(size);
		std::memcpy(data, mappedData, size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);

		return std::unique_ptr<void, decltype(zt::core::LambdaFree)>{ data };
	}

	void Buffer::fillWithCArray(const void* cArray, std::uint64_t cArraySize)
	{
		if (size < cArraySize)
			cArraySize = size;

		void* mappedData = nullptr;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		std::memcpy(mappedData, cArray, cArraySize);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, cArraySize);
	}

	void Buffer::create(const CreateInfo& bufferCreateInfo)
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
			vk::raii::Buffer tempBuffer{ bufferCreateInfo.device.getInternal(), buffer };
			internal.swap(tempBuffer);
			tempBuffer.release();
		}
		else
		{
			Logger->error("Failed to create Buffer");
			zt::core::Ensure(false);
		}

	}

	VmaAllocationCreateInfo Buffer::createVmaAllocationCreateInfo(bool randomAccess, bool useCPUMemory) const
	{
		VmaAllocationCreateInfo allocationCreateInfo{};

		if (randomAccess)
		{
			allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT;
		}
		else
		{
			allocationCreateInfo.flags = VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
		}
		
		if (useCPUMemory)
		{
			allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
		}
		else
		{
			allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
		}

		return allocationCreateInfo;
	}

}