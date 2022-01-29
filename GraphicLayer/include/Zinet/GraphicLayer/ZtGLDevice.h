#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLQueue.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

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

		vk::DeviceCreateInfo createDeviceCreateInfo(const PhysicalDevice& physicalDevice) const;

		void create(const PhysicalDevice& physicalDevice);

		const vk::raii::Device& getInternal() const;

		vk::raii::Queue createQueue(uint32_t queueFamilyIndex) const;

	protected:

		vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
		// Needed to deviceQueueCreateInfo
		float queuePriority = 1.0f;

		vk::raii::Device internal;
	};

}