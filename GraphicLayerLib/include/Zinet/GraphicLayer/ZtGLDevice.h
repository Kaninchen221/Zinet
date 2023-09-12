#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Instance;
	class PhysicalDevice;
	class Queue;
	class Surface;
	class Fence;

	class ZINET_GRAPHIC_LAYER_API Device : public VulkanObject<vk::raii::Device>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Device");

	public:

		Device() = default;
		Device(const Device& other) = default;
		Device(Device&& other) = default;

		Device& operator = (const Device& other) = default;
		Device& operator = (Device&& other) = default;

		~Device() noexcept = default;

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(PhysicalDevice& physicalDevice, Surface& surface);

		vk::DeviceCreateInfo createDeviceCreateInfo(const Instance& instance, PhysicalDevice& physicalDevice, Surface& surface, vk::DeviceQueueCreateInfo& deviceQueueCreateInfo);

		void create(PhysicalDevice& physicalDevice, vk::DeviceCreateInfo& deviceCreateInfo);

		vk::Result waitForFence(Fence& fence, uint64_t timeout = UINT64_MAX) const;

		void resetFence(Fence& fence) const;

	protected:

		float queuePriority = 1.0f;

	};

}