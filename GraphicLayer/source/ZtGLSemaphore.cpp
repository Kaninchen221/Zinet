#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	Semaphore::Semaphore()
		: internal{ std::nullptr_t{} }
	{
	}

	vk::raii::Semaphore& Semaphore::getInternal()
	{
		return internal;
	}

	vk::SemaphoreCreateInfo Semaphore::createSemaphoreCreateInfo()
	{
		return vk::SemaphoreCreateInfo();
	}

	void Semaphore::create(Device& device)
	{
		vk::SemaphoreCreateInfo createInfo = createSemaphoreCreateInfo();
		internal = std::move(vk::raii::Semaphore{ device.getInternal(), createInfo });
	}

	uint64_t Semaphore::getCounterValue() const
	{
		return internal.getCounterValue();
	}
}
