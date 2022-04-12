#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API DebugUtilsMessenger
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("DebugUtilsMessenger");

	public:

		DebugUtilsMessenger();
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

		const vk::raii::DebugUtilsMessengerEXT& getDebugMessenger() const;

		void createDebugUtilsMessenger(Instance& instance);

	protected:

		vk::raii::DebugUtilsMessengerEXT debugUtilsMessenger;

	};

}