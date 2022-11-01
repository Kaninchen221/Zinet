#include "Zinet/GraphicLayer/ZtGLVertexBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"

namespace zt::gl
{
	VertexBuffer::~VertexBuffer() noexcept
	{
		if (allocation != nullptr)
		{
			vmaDestroyBuffer(vma->getInternal(), nullptr, allocation);
		}
	}

	vk::BufferCreateInfo VertexBuffer::createCreateInfo(std::uint64_t size) const
	{
		vk::BufferCreateInfo bufferCreateInfo;
		bufferCreateInfo.size = size;
		bufferCreateInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst;
		bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

		return bufferCreateInfo;
	}

	VmaAllocationCreateInfo VertexBuffer::createVmaAllocationCreateInfo(bool randomAccess) const
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

	void VertexBuffer::create(const Renderer& renderer, const VkBufferCreateInfo& bufferCreateInfo, const VmaAllocationCreateInfo& allocationCreateInfo)
	{
		vma = &renderer.getVma();
		VkBuffer buffer;
		vmaCreateBuffer(vma->getInternal(), &bufferCreateInfo, &allocationCreateInfo, &buffer, &allocation, nullptr);
		size = bufferCreateInfo.size;
		internal = vk::raii::Buffer{ renderer.getDevice().getInternal(), buffer };
	}

}