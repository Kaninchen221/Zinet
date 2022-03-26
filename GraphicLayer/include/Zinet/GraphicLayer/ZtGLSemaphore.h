#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "Zinet/Core/ZtLogger.h"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Semaphore
	{

	protected:

		static inline zt::Logger::SimpleConsoleLogger Logger = zt::Logger::CreateSimpleConsoleLogger("Semaphore");

	public:

		Semaphore();
		Semaphore(const Semaphore& other) = default;
		Semaphore(Semaphore&& other) = default;

		Semaphore& operator = (const Semaphore& other) = default;
		Semaphore& operator = (Semaphore&& other) = default;

		~Semaphore() noexcept = default;

		vk::raii::Semaphore& getInternal();

		vk::SemaphoreCreateInfo createSemaphoreCreateInfo();

		void create(Device& device);

		uint64_t getCounterValue() const;

	protected:

		vk::raii::Semaphore internal;

	};

}
