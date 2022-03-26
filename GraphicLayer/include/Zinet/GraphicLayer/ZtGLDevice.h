#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class PhysicalDevice;
	class Queue;
	class Surface;
	class Fence;

	class ZINET_GRAPHIC_LAYER_API Device
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Device");

	public:

		Device();
		Device(const Device& other) = default;
		Device(Device&& other) = default;

		Device& operator = (const Device& other) = default;
		Device& operator = (Device&& other) = default;

		~Device() noexcept = default;

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(const PhysicalDevice& physicalDevice, const Surface& surface);

		vk::DeviceCreateInfo createDeviceCreateInfo(const PhysicalDevice& physicalDevice, const Surface& surface);

		void create(const PhysicalDevice& physicalDevice, const Surface& surface);

		vk::raii::Device& getInternal();

		vk::raii::Queue createQueue(uint32_t queueFamilyIndex) const;

		vk::Result waitForFence(Fence& fence, uint64_t timeout) const;

	protected:

		vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
		// Needed to deviceQueueCreateInfo
		float queuePriority = 1.0f;

		vk::raii::Device internal;
	};

}