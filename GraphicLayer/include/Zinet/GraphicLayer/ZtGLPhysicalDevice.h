#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API PhysicalDevice
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("PhysicalDevice");

	public:

		PhysicalDevice() = default;
		PhysicalDevice(const PhysicalDevice& other) = default;
		PhysicalDevice(PhysicalDevice&& other) = default;

		PhysicalDevice& operator = (const PhysicalDevice& other) = default;
		PhysicalDevice& operator = (PhysicalDevice&& other) = default;

		~PhysicalDevice() noexcept = default;

		uint32_t pickQueueFamilyIndex(const vk::raii::PhysicalDevice& physicalDevice) const;

		vk::PhysicalDeviceFeatures createPhysicalDeviceFeatures() const;

	public:

		vk::PhysicalDeviceFeatures physicalDeviceFeatures;

	};

}