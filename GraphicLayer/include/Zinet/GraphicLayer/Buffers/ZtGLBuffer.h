#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLVma.h"

#include "Zinet/Core/ZtLogger.h"

#include <vk_mem_alloc.h>

namespace zt::gl
{
	class Renderer;
	class Vma;

	class ZINET_GRAPHIC_LAYER_API Buffer : public VulkanObject<vk::raii::Buffer>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Buffer");

	public:

		Buffer() = default;
		Buffer(const Buffer& other) = default;
		Buffer(Buffer&& other) = default;

		Buffer& operator = (const Buffer& other) = default;
		Buffer& operator = (Buffer&& other) = default;

		~Buffer() noexcept;

		virtual vk::BufferCreateInfo createCreateInfo(std::uint64_t size) const = 0;

		virtual VmaAllocationCreateInfo createVmaAllocationCreateInfo(bool randomAccess) const;

		void create(const Renderer& renderer, const VkBufferCreateInfo& bufferCreateInfo, const VmaAllocationCreateInfo& allocationCreateInfo);

		std::uint64_t getSize() const;

		template<typename T>
		void fillWithObject(const T& object);

		template<typename T>
		void fillWithStdContainer(const T& container);

		void fillWithCArray(void* firstElement);

		std::pair<void*, std::uint64_t> getData();

	private:

		std::uint64_t size{};
		const Vma* vma{};
		VmaAllocation allocation = nullptr;

	};

	template<typename T>
	inline void Buffer::fillWithObject(const T& object)
	{
		void* mappedData;
		vmaMapMemory(vma->getInternal(), allocation, &mappedData);
		std::memcpy(mappedData, &object, size);
		vmaUnmapMemory(vma->getInternal(), allocation);
	}

	template<typename T>
	inline void Buffer::fillWithStdContainer(const T& container)
	{
		void* mappedData;
		vmaMapMemory(vma->getInternal(), allocation, &mappedData);
		std::memcpy(mappedData, container.data(), size);
		vmaUnmapMemory(vma->getInternal(), allocation);
	}
}