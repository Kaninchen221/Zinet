#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Instance
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Instance");

	public:

		Instance();
		Instance(const Instance& other) = default;
		Instance(Instance&& other) = default;

		Instance& operator = (const Instance& other) = default;
		Instance& operator = (Instance&& other) = default;

		~Instance() noexcept = default;

		void createApplicationInfo();
		const vk::ApplicationInfo& getApplicationInfo() const;

		void createInstanceCreateInfo();
		const vk::InstanceCreateInfo& getInstanceCreateInfo() const;

		void createInstance(const Context& context);
		const vk::raii::Instance& getInstance() const;

		const std::vector<const char*>& getValidationLayers() const;

		bool checkValidationLayerSupport() const;

		std::vector<const char*> getRequiredExtensions();

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		vk::raii::PhysicalDevice pickPhysicalDevice() const;

	public:

		vk::ApplicationInfo applicationInfo{};

		vk::InstanceCreateInfo instanceCreateInfo{};
		vk::raii::Instance instance;

		std::vector<const char*> extensions;

#ifdef ZINET_DEBUG
		const bool enableValidationLayers = true;
#else
		const bool enableValidationLayers = false;
#endif

		const std::vector<const char*> validationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};
	};

}