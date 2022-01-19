#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Queue
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Queue");

	public:

		Queue() = delete;
		Queue(const Queue& other) = default;
		Queue(Queue&& other) = default;
		Queue(vk::raii::Queue&& queue);

		Queue& operator = (const Queue& other) = default;
		Queue& operator = (Queue&& other) = default;

		~Queue() noexcept = default;

		const vk::raii::Queue& getInternal() const;

	protected:

		vk::raii::Queue internal;

	};

}