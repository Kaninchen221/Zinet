#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"

#include "Zinet/Core/ZtLogger.h"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Vma;
	class Device;

	struct BufferCreateInfo
	{
		const Device& device;
		const Vma& vma;
		VkBufferCreateInfo vkBufferCreateInfo;
		VmaAllocationCreateInfo allocationCreateInfo;
	};

	// TODO Flush Vma allocator after unmap operation if mapped memory is not HOST_COHERENT
	class ZINET_GRAPHIC_LAYER_API Buffer : public VulkanObject<vk::raii::Buffer>
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Buffer");

	public:

		Buffer() = default;
		Buffer(const Buffer& other) = default;
		Buffer(Buffer&& other) = default;

		Buffer& operator = (const Buffer& other) = default;
		Buffer& operator = (Buffer&& other) = default;

		virtual ~Buffer() noexcept;

		virtual vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const = 0;

		virtual VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess, bool useCPUMemory) const;

		void create(const BufferCreateInfo& bufferCreateInfo);

		std::uint64_t getSize() const;

		template<typename T>
		void fillWithObject(const T& object);

		template<typename T>
		void fillWithStdContainer(const T& container);

		void fillWithCArray(const void* firstElement);

		std::pair<void*, std::uint64_t> getData();

	private:

		std::uint64_t size{};
		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};

	};

	template<typename T>
	inline void Buffer::fillWithObject(const T& object)
	{
		void* mappedData;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		std::memcpy(mappedData, &object, size);
		vmaUnmapMemory(vmaAllocator, allocation);
		//vmaFlushAllocation(vmaAllocator, allocation, 0, size);
	}

	template<typename T>
	inline void Buffer::fillWithStdContainer(const T& container)
	{
		void* mappedData;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		std::memcpy(mappedData, container.data(), size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);
	}
}