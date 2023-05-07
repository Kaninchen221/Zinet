#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class PhysicalDevice;
	class Queue;
	class Surface;
	class Fence;

	class ZINET_GRAPHIC_LAYER_API Device : public VulkanObject<vk::raii::Device>
	{

	protected:

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Device");

	public:

		Device();
		Device(const Device& other) = default;
		Device(Device&& other) = default;

		Device& operator = (const Device& other) = default;
		Device& operator = (Device&& other) = default;

		~Device() noexcept;

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(PhysicalDevice& physicalDevice, Surface& surface);

		vk::DeviceCreateInfo createDeviceCreateInfo(PhysicalDevice& physicalDevice, Surface& surface, vk::DeviceQueueCreateInfo& deviceQueueCreateInfo);

		void create(PhysicalDevice& physicalDevice, vk::DeviceCreateInfo& deviceCreateInfo);

		vk::Result waitForFence(Fence& fence, uint64_t timeout = UINT64_MAX) const;

		void resetFence(Fence& fence) const;

	protected:

		float queuePriority = 1.0f;

	};

}