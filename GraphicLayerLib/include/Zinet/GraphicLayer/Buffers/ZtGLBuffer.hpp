#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLVma.hpp"

#include "Zinet/Core/ZtLogger.hpp"
#include "Zinet/Core/ZtTypeTraits.hpp"

namespace zt::gl
{
	class Vma;
	class Device;

	class ZINET_GRAPHIC_LAYER_API Buffer : public VulkanObject<vk::raii::Buffer>
	{
	public:

		struct CreateInfo
		{
			const Device& device;
			const Vma& vma;
			VkBufferCreateInfo vkBufferCreateInfo;
			VmaAllocationCreateInfo allocationCreateInfo;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Buffer");

	public:

		Buffer() = default;
		Buffer(const Buffer& other) = delete;
		Buffer(Buffer&& other);

		Buffer& operator = (const Buffer& other) = delete;
		Buffer& operator = (Buffer&& other);

		virtual ~Buffer() noexcept;

		virtual vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const = 0;

		virtual VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess, bool useCPUMemory) const;

		void create(const CreateInfo& bufferCreateInfo);

		std::uint64_t getSize() const;

		template<typename T>
		void fillWithObject(const T& object);

		template<typename T>
		void fillWithStdContainer(const T& container);

		void fillWithCArray(const void* cArray, std::uint64_t cArraySize);

		std::unique_ptr<void, decltype(zt::core::LambdaFree)> getData();

	private:

		std::uint64_t size{};
		VmaAllocator vmaAllocator{};
		VmaAllocation allocation{};

	};

	template<typename T>
	inline void Buffer::fillWithObject(const T& object)
	{
		void* mappedData = nullptr;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		std::memcpy(mappedData, &object, size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);
	}

	template<typename T>
	inline void Buffer::fillWithStdContainer(const T& container)
	{
		void* mappedData = nullptr;
		VkResult mapMemoryResult = vmaMapMemory(vmaAllocator, allocation, &mappedData);
		if (mapMemoryResult != VK_SUCCESS)
			Logger->error("Failed to map memory");

		std::memcpy(mappedData, container.data(), size);
		vmaUnmapMemory(vmaAllocator, allocation);
		vmaFlushAllocation(vmaAllocator, allocation, 0, size);
	}
}