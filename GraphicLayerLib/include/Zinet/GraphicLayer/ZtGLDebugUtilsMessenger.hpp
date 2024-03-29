#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLInstance.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API DebugUtilsMessenger : public VulkanObject<vk::raii::DebugUtilsMessengerEXT>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("DebugUtilsMessenger");

	public:

		DebugUtilsMessenger() = default;
		DebugUtilsMessenger(const DebugUtilsMessenger& other) = default;
		DebugUtilsMessenger(DebugUtilsMessenger&& other) = default;

		DebugUtilsMessenger& operator = (const DebugUtilsMessenger& other) = default;
		DebugUtilsMessenger& operator = (DebugUtilsMessenger&& other) = default;

		~DebugUtilsMessenger() noexcept = default;

		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageType,
			const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
			void* userData);

		void create(Instance& instance);

	};

}