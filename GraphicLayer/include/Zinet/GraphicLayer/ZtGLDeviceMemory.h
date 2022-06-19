#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

#include <any>

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API DeviceMemory : public VulkanObject<vk::raii::DeviceMemory>
	{

	public:

		DeviceMemory() = default;
		DeviceMemory(const DeviceMemory& other) = default;
		DeviceMemory(DeviceMemory&& other) = default;

		DeviceMemory& operator = (const DeviceMemory& other) = default;
		DeviceMemory& operator = (DeviceMemory&& other) = default;

		~DeviceMemory() noexcept = default;

		void create(Device& device, const vk::MemoryAllocateInfo& memoryAllocateInfo);

		template<typename Data>
		void fillWithSTDContainer(const Data& data);

		template<typename Object>
		void fillWithObject(const Object& object);

		void fillWithArray(const void* const array, std::size_t size);

		std::pair<void*, std::uint64_t> getData(vk::DeviceSize size) const;

	};

	template<typename Data>
	inline void DeviceMemory::fillWithSTDContainer(const Data& data)
	{
		vk::DeviceSize offset = 0u;
		vk::DeviceSize size = sizeof(Data::value_type) * data.size();
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, data.data(), size);

		internal.unmapMemory();
	}

	template<typename Object>
	inline void DeviceMemory::fillWithObject(const Object& object)
	{
		vk::DeviceSize offset = 0u;
		vk::DeviceSize size = sizeof(Object);
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, &object, size);

		internal.unmapMemory();
	}

}