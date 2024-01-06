#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLContext.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Instance : public VulkanObject<vk::raii::Instance>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Instance");

	public:

		Instance() = default;
		Instance(const Instance& other) = default;
		Instance(Instance&& other) = default;

		Instance& operator = (const Instance& other) = default;
		Instance& operator = (Instance&& other) = default;

		~Instance() noexcept = default;

		vk::ApplicationInfo createApplicationInfo() const;

		vk::InstanceCreateInfo createInstanceCreateInfo(const vk::ApplicationInfo& applicationInfo) const;

		void create(Context& context, vk::InstanceCreateInfo createInfo);

		vk::raii::PhysicalDevices enumeratePhysicalDevices() const;

		static const std::vector<const char*>& GetValidationLayers();

		static bool CheckValidationLayerSupport();

		std::vector<const char*>& getRequiredExtensions();

		void populateRequiredExtensions();

		void setEnableValidationLayers(bool enable) { enableValidationLayers = enable; }

		bool getEnableValidationLayers() const { return enableValidationLayers; }

	public:

		std::vector<const char*> extensions;

		inline static const std::vector<const char*> ValidationLayers =
		{
			"VK_LAYER_KHRONOS_validation"
		};

		bool enableValidationLayers = true;
	};

}