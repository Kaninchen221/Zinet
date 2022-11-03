#include "Zinet/GraphicLayer/ZtGLBuffer.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"
//#include "Zinet/GraphicLayer/ZtGLVma.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	Buffer::~Buffer()
	{
		if (allocation != nullptr)
		{
			vmaDestroyBuffer(vma->getInternal(), nullptr, allocation);
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

		vk::DeviceSize offset = 0u;
		void* mappedData;
		vmaMapMemory(vma->getInternal(), allocation, &mappedData);
		std::memcpy(result.first, mappedData, size);

		vmaUnmapMemory(vma->getInternal(), allocation);

		return result;
	}

	void Buffer::fillWithCArray(void* firstElement, std::size_t size)
	{
		void* mappedData;
		vmaMapMemory(vma->getInternal(), allocation, &mappedData);
		std::memcpy(mappedData, firstElement, size);
		vmaUnmapMemory(vma->getInternal(), allocation);
	}

	void Buffer::create(const Renderer& renderer, const VkBufferCreateInfo& bufferCreateInfo, const VmaAllocationCreateInfo& allocationCreateInfo)
	{
		vma = &renderer.getVma();
		VkBuffer buffer;
		vmaCreateBuffer(vma->getInternal(), &bufferCreateInfo, &allocationCreateInfo, &buffer, &allocation, nullptr);
		size = bufferCreateInfo.size;
		internal = vk::raii::Buffer{ renderer.getDevice().getInternal(), buffer };
	}

	VmaAllocationCreateInfo Buffer::createVmaAllocationCreateInfo(bool randomAccess) const
	{
		VmaAllocationCreateInfo allocationCreateInfo{};
		allocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;

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