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
		void fillWithData(const Data& data);

		std::pair<void*, std::uint64_t> getData(vk::DeviceSize size) const;

	};

	template<typename Data>
	inline void DeviceMemory::fillWithData(const Data& data)
	{
		vk::DeviceSize offset = 0u;
		vk::DeviceSize size = sizeof(Data::value_type) * data.size();
		void* memory = internal.mapMemory(offset, size);

		std::memcpy(memory, data.data(), size);

		internal.unmapMemory();
	}

}