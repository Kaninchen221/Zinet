#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLContext.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Instance : public VulkanObject<vk::raii::Instance>
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

		// TODO Perhaps create this as one function
		void createApplicationInfo();
		const vk::ApplicationInfo& getApplicationInfo() const;

		// TODO Perhaps create this as one function
		void createInstanceCreateInfo();
		const vk::InstanceCreateInfo& getInstanceCreateInfo() const;

		void create(Context& context);

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		static const std::vector<const char*>& GetValidationLayers();

		// TODO Make non static function
		static bool CheckValidationLayerSupport();

		std::vector<const char*> getRequiredExtensions();

		static bool GetEnabledValidationLayers();

	public:

		vk::ApplicationInfo applicationInfo{};

		vk::InstanceCreateInfo instanceCreateInfo{};

		std::vector<const char*> extensions;

		// TODO Move this as return value of function GetValidationLayers
		inline static const std::vector<const char*> ValidationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

	};

}