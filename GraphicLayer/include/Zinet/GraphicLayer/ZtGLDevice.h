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

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(PhysicalDevice& physicalDevice, Surface& surface);

		vk::DeviceCreateInfo createDeviceCreateInfo(PhysicalDevice& physicalDevice, Surface& surface);

		void create(PhysicalDevice& physicalDevice, Surface& surface);

		vk::raii::Device& getInternal();

		// TODO: Move to Queue class?
		vk::raii::Queue createQueue(uint32_t queueFamilyIndex) const;

		vk::Result waitForFence(Fence& fence, uint64_t timeout) const;

		void resetFence(Fence& fence) const;

	protected:

		vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
		// Needed to deviceQueueCreateInfo
		float queuePriority = 1.0f;

		vk::raii::Device internal;
	};

}