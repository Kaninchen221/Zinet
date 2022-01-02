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

		Context() = default;
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
		const vk::Instance& getInstance() const;
		
		void createPhysicalDevices();
		const std::vector<vk::PhysicalDevice>& getPhysicalDevices() const;

		const std::vector<const char*>& getValidationLayers() const;

		bool checkValidationLayerSupport() const;

		std::vector<const char*> getRequiredExtensions();

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
			void* userData);

		const VkDebugUtilsMessengerEXT& getDebugMessenger() const;

		void createDebugUtilsMessengerCreateInfo();
		const VkDebugUtilsMessengerCreateInfoEXT& getDebugUtilsMessengerCreateInfo() const;

		VkResult createDebugUtilsMessenger();

		void destroyDebugUtilsMessengerCreateInfo();

		VkResult initVulkan();

	protected:

		vk::ApplicationInfo applicationInfo{};

		vk::InstanceCreateInfo instanceCreateInfo{};
		vk::Instance instance;

		std::vector<const char*> extensions;

		VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo{};
		VkDebugUtilsMessengerEXT debugMessenger;

	#ifdef ZINET_DEBUG
		const bool enableValidationLayers = true;
	#else
		const bool enableValidationLayers = false;
	#endif

		const std::vector<const char*> validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

		std::vector<vk::PhysicalDevice> physicalDevices;
	};

}