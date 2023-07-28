#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Fence : public VulkanObject<vk::raii::Fence>
	{

	protected:
		
		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Fence");

	public:

		Fence() = default;
		Fence(const Fence& other) = default;
		Fence(Fence&& other) = default;

		Fence& operator = (const Fence& other) = default;
		Fence& operator = (Fence&& other) = default;

		~Fence() noexcept = default;

		vk::FenceCreateInfo createSignaledFenceCreateInfo();

		vk::FenceCreateInfo createUnsignaledFenceCreateInfo();

		void create(Device& device, const vk::FenceCreateInfo& createInfo);

		vk::Result getStatus() const;
	};

}
