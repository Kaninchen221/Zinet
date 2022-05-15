#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;
	class DeviceMemory;

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

		~Buffer() noexcept = default;

		virtual vk::BufferCreateInfo createCreateInfo() const = 0;

		void create(Device& device, const vk::BufferCreateInfo& createInfo);

		uint32_t findSuitableMemoryType(
			const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
			const vk::MemoryPropertyFlags& memoryPropertyFlags) const;

		vk::MemoryAllocateInfo createMemoryAllocateInfo(
			const vk::PhysicalDeviceMemoryProperties& physicalDeviceMemoryProperties, 
			const vk::MemoryPropertyFlags& memoryPropertyFlags) const;

		void bindMemory(DeviceMemory& deviceMemory);

		void setSize(std::uint64_t size);

		std::uint64_t getSize() const;

	protected:

		// TODO: Move it as function param to createCreateInfo
		std::uint64_t size{};

	};

}