#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{
	class Device;

	class ZINET_GRAPHIC_LAYER_API Semaphore : public VulkanObject<vk::raii::Semaphore>
	{

	protected:

		inline static zt::core::ConsoleLogger Logger = zt::core::ConsoleLogger::Create("Semaphore");

	public:

		Semaphore() = default;
		Semaphore(const Semaphore& other) = default;
		Semaphore(Semaphore&& other) = default;

		Semaphore& operator = (const Semaphore& other) = default;
		Semaphore& operator = (Semaphore&& other) = default;

		~Semaphore() noexcept = default;

		vk::SemaphoreCreateInfo createSemaphoreCreateInfo();

		void create(Device& device);

		uint64_t getCounterValue() const;

	};

}
