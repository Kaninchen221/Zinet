#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Fence
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Fence");

	public:

		Fence();
		Fence(const Fence& other) = default;
		Fence(Fence&& other) = default;

		Fence& operator = (const Fence& other) = default;
		Fence& operator = (Fence&& other) = default;

		~Fence() noexcept = default;

		vk::raii::Fence& getInternal();

		vk::FenceCreateInfo createFenceCreateInfo();

		void createUnsignaled(Device& device);

		void createSignaled(Device& device);

		vk::Result getStatus() const;

	protected:

		vk::raii::Fence internal;

	};

}
