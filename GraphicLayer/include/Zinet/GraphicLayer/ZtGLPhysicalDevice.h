#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Surface;
	class Instance;

	class ZINET_GRAPHIC_LAYER_API PhysicalDevice : public VulkanObject<vk::raii::PhysicalDevice>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("PhysicalDevice");

	public:

		PhysicalDevice() = default;
		PhysicalDevice(const PhysicalDevice& other) = default;
		PhysicalDevice(PhysicalDevice&& other) = default;

		PhysicalDevice& operator = ([[maybe_unused]] const PhysicalDevice& other) { return *this; };
		PhysicalDevice& operator = (PhysicalDevice&& PhysicalDevice) = default;

		~PhysicalDevice() noexcept = default;

		uint32_t pickQueueFamilyIndex(const Surface& surface) const;

		const vk::PhysicalDeviceFeatures& getFeatures() const;

		bool create(Instance& instance);

		const std::vector<const char*>& getPhysicalDeviceExtensions() const;

		bool isDeviceHasNeededExtensions(const vk::raii::PhysicalDevice& physicalDevice) const;

		SwapChainSupportDetails getSwapChainSupportDetails(const Surface& surface) const;

	protected:
		
		vk::PhysicalDeviceFeatures features;

		const std::vector<const char*> physicalDeviceExtensions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};

}