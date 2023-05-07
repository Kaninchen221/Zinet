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

		inline static ConsoleLogger Logger = ConsoleLogger::Create("Fence");

	public:

		Fence();
		Fence(const Fence& other) = default;
		Fence(Fence&& other) = default;

		Fence& operator = (const Fence& other) = default;
		Fence& operator = (Fence&& other) = default;

		~Fence() noexcept = default;

		vk::FenceCreateInfo createFenceCreateInfo();

		void createUnsignaled(Device& device);

		void createSignaled(Device& device);

		vk::Result getStatus() const;
	};

}
