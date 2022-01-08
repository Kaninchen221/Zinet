#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Context
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Context");

	public:

		Context();
		Context(const Context& other) = default;
		Context(Context&& other) = default;

		Context& operator = (const Context& other) = default;
		Context& operator = (Context&& other) = default;

		~Context() noexcept;

		bool initGLFW();

		void deinitGLFW();

		void createApplicationInfo();
		const vk::ApplicationInfo& getApplicationInfo() const;

		void createInstanceCreateInfo();
		const vk::InstanceCreateInfo& getInstanceCreateInfo() const;

		void createInstance();
		const vk::raii::Instance& getInstance() const;

		const std::vector<const char*>& getValidationLayers() const;

		bool checkValidationLayerSupport() const;

		std::vector<const char*> getRequiredExtensions();

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
			void* userData);

		const vk::raii::DebugUtilsMessengerEXT& getDebugMessenger() const;

		void createDebugUtilsMessenger();

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		vk::raii::PhysicalDevice pickPhysicalDevice() const;

		uint32_t pickQueueFamilyIndex(const vk::raii::PhysicalDevice& physicalDevice) const;

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(const vk::raii::PhysicalDevice& physicalDevice);

		vk::PhysicalDeviceFeatures createPhysicalDeviceFeatures() const;

		vk::DeviceCreateInfo createDeviceCreateInfo() const;

		vk::raii::Device createDevice(const vk::raii::PhysicalDevice& physicalDevice);

		vk::raii::Queue createQueue(const vk::raii::Device& device, uint32_t queueFamilyIndex) const;

	protected:

		vk::raii::Context context;

		vk::ApplicationInfo applicationInfo{};

		vk::InstanceCreateInfo instanceCreateInfo{};
		vk::raii::Instance instance;

		std::vector<const char*> extensions;

		vk::raii::DebugUtilsMessengerEXT debugMessenger;

	#ifdef ZINET_DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif

		const std::vector<const char*> validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

		vk::PhysicalDeviceFeatures physicalDeviceFeatures;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
		// Needed to deviceQueueCreateInfo
		float queuePriority = 1.0f;
	};

}