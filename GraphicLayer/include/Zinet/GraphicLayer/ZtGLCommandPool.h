#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API CommandPool : public VulkanObject<vk::raii::CommandPool>
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("CommandPool");

	public:

		CommandPool();
		CommandPool(const CommandPool& other) = default;
		CommandPool(CommandPool&& other) = default;

		CommandPool& operator = (const CommandPool& other) = default;
		CommandPool& operator = (CommandPool&& other) = default;

		~CommandPool() noexcept = default;

		vk::CommandPoolCreateInfo createCommandPoolCreateInfo(uint32_t queueFamilyIndex) const;

		void create(const Device& device, uint32_t queueFamilyIndex);

	};

}
