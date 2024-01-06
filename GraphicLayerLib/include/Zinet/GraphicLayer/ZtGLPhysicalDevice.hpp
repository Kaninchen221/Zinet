#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"
#include "Zinet/GraphicLayer/ZtGLSwapChainSupportDetails.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Surface;
	class Instance;

	class ZINET_GRAPHIC_LAYER_API PhysicalDevice : public VulkanObject<vk::raii::PhysicalDevice>
	{
	public:

		struct FindSupportedFormatInput
		{
			const std::vector<vk::Format>& candidates;
			vk::ImageTiling imageTiling;
			vk::FormatFeatureFlags formatFeatureFlags;
		};

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("PhysicalDevice");

	public:

		PhysicalDevice() = default;
		PhysicalDevice(const PhysicalDevice& other) = default;
		PhysicalDevice(PhysicalDevice&& other) = default;

		PhysicalDevice& operator = (const PhysicalDevice& other) { return *this; };
		PhysicalDevice& operator = (PhysicalDevice&& PhysicalDevice) = default;

		~PhysicalDevice() noexcept = default;

		uint32_t pickQueueFamilyIndex(const Surface& surface) const;

		const vk::PhysicalDeviceFeatures& getFeatures() const;

		bool create(Instance& instance);

		std::int16_t ratePhysicalDevice(const vk::raii::PhysicalDevice& physicalDevice);

		bool hasRequiredExtensions(const vk::raii::PhysicalDevice& physicalDevice) const;

		const std::vector<const char*>& getPhysicalDeviceExtensions() const;

		SwapChainSupportDetails getSwapChainSupportDetails(const Surface& surface) const;

		bool findSupportedFormat(const FindSupportedFormatInput& input, vk::Format& supportedFormat) const;

		bool isFormatSupportingGeneratingMipmaps(vk::Format format) const;

	protected:
		
		vk::PhysicalDeviceFeatures features;

		const std::vector<const char*> physicalDeviceExtensions =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};
	};

}