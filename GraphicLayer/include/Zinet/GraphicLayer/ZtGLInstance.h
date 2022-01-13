#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

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
		const vk::raii::Instance& getInternal() const;

		static const std::vector<const char*>& GetValidationLayers();

		static bool CheckValidationLayerSupport();

		std::vector<const char*> getRequiredExtensions();

		static bool GetEnabledValidationLayers();

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		PhysicalDevice pickPhysicalDevice() const;

	public:

		vk::ApplicationInfo applicationInfo{};

		vk::InstanceCreateInfo instanceCreateInfo{};
		vk::raii::Instance internal;

		std::vector<const char*> extensions;

		inline static const std::vector<const char*> ValidationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};
	};

}