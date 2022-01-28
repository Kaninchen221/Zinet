#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLSurface.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API PhysicalDevice
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("PhysicalDevice");

	public:

		PhysicalDevice();
		PhysicalDevice(const PhysicalDevice& other) = default;
		PhysicalDevice(PhysicalDevice&& other) = default;
		PhysicalDevice(vk::raii::PhysicalDevice&& physicalDevice);

		PhysicalDevice& operator = (const PhysicalDevice& other) = default;
		PhysicalDevice& operator = (PhysicalDevice&& PhysicalDevice) = default;

		~PhysicalDevice() noexcept = default;

		uint32_t pickQueueFamilyIndex(const Surface& surface) const;

		vk::PhysicalDeviceFeatures createFeatures() const;

		const vk::PhysicalDeviceFeatures& getFeatures() const;

		const vk::raii::PhysicalDevice& getInternal() const;

		vk::raii::PhysicalDevices enumeratePhysicalDevices(const Instance& instance) const;

		bool create(const Instance& instance);

		static const std::vector<std::array<char, VK_MAX_EXTENSION_NAME_SIZE>>& GetPhysicalDeviceExtensions();

		bool isDeviceHasNeededExtensions(const vk::raii::PhysicalDevice& physicalDevice) const;

	protected:

		vk::raii::PhysicalDevice internal;
		vk::PhysicalDeviceFeatures features;

		inline static const std::vector<std::array<char, VK_MAX_EXTENSION_NAME_SIZE>> PhysicalDeviceExtensions =
		{
			{ VK_KHR_SWAPCHAIN_EXTENSION_NAME }
		};
	};

}