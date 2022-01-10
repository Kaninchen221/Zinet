#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLInstance.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLPhysicalDevice.h"

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

		vk::DeviceQueueCreateInfo createDeviceQueueCreateInfo(const vk::raii::PhysicalDevice& physicalDevice);

		vk::DeviceCreateInfo createDeviceCreateInfo() const;

		vk::raii::Device createDevice(const vk::raii::PhysicalDevice& physicalDevice);

		vk::raii::Queue createQueue(const vk::raii::Device& device, uint32_t queueFamilyIndex) const;

	public:

		vk::raii::Context context;

		Instance instanceHelper;

		PhysicalDevice physicalDeviceHelper;

		vk::DeviceQueueCreateInfo deviceQueueCreateInfo;
		// Needed to deviceQueueCreateInfo
		float queuePriority = 1.0f;
	};

}