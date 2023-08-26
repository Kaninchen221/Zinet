#include "Zinet/GraphicLayer/ZtGLSemaphore.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	vk::SemaphoreCreateInfo Semaphore::createSemaphoreCreateInfo()
	{
		return vk::SemaphoreCreateInfo();
	}

	void Semaphore::create(Device& device)
	{
		vk::SemaphoreCreateInfo createInfo = createSemaphoreCreateInfo();
		vk::raii::Semaphore tempSemaphore{ device.getInternal(), createInfo };
		internal.swap(tempSemaphore);
		tempSemaphore.release();
	}

	uint64_t Semaphore::getCounterValue() const
	{
		return internal.getCounterValue();
	}
}
