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

		Instance() = default;
		Instance(const Instance& other) = default;
		Instance(Instance&& other) = default;

		Instance& operator = (const Instance& other) = default;
		Instance& operator = (Instance&& other) = default;

		~Instance() noexcept = default;

		vk::ApplicationInfo createApplicationInfo() const;

		vk::InstanceCreateInfo createInstanceCreateInfo(vk::ApplicationInfo applicationInfo) const;

		void create(Context& context, vk::InstanceCreateInfo createInfo);

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		static const std::vector<const char*>& GetValidationLayers();

		static bool CheckValidationLayerSupport();

		std::vector<const char*>& getRequiredExtensions();

		void populateRequiredExtensions();

		static bool GetEnabledValidationLayers();

	public:

		std::vector<const char*> extensions;

		inline static const std::vector<const char*> ValidationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

	};

}