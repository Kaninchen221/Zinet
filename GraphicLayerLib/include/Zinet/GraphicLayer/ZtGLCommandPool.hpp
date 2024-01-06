#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API CommandPool : public VulkanObject<vk::raii::CommandPool>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("CommandPool");

	public:

		CommandPool() = default;
		CommandPool(const CommandPool& other) = default;
		CommandPool(CommandPool&& other) = default;

		CommandPool& operator = (const CommandPool& other) = default;
		CommandPool& operator = (CommandPool&& other) = default;

		~CommandPool() noexcept = default;

		vk::CommandPoolCreateInfo createCommandPoolCreateInfo(uint32_t queueFamilyIndex) const;

		void create(const Device& device, uint32_t queueFamilyIndex);

	};

}
