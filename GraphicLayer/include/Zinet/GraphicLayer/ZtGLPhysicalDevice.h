#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

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

		PhysicalDevice(); // TODO remove definition and add '= default'
		PhysicalDevice(const PhysicalDevice& other) = default;
		PhysicalDevice(PhysicalDevice&& other) = default;
		PhysicalDevice(vk::raii::PhysicalDevice&& physicalDevice);

		PhysicalDevice& operator = (const PhysicalDevice& other) = default;
		PhysicalDevice& operator = (PhysicalDevice&& PhysicalDevice) = default;

		~PhysicalDevice() noexcept = default;

		uint32_t pickQueueFamilyIndex(Surface& surface);

		vk::PhysicalDeviceFeatures createFeatures() const;
		const vk::PhysicalDeviceFeatures& getFeatures() const;

		bool create(Instance& instance);

		// TODO Convert it to non static function
		static const std::vector<const char*>& GetPhysicalDeviceExtensions();

		bool isDeviceHasNeededExtensions(const vk::raii::PhysicalDevice& physicalDevice) const;

		SwapChainSupportDetails getSwapChainSupportDetails(Surface& surface);

	protected:
		
		// TODO Return it as value in createFeatures
		vk::PhysicalDeviceFeatures features;

		// TODO Return it as value in GetPhysicalDeviceExtensions
		inline static const std::vector<const char*> PhysicalDeviceExtensions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};

}