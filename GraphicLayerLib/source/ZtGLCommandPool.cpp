#include "Zinet/GraphicLayer/ZtGLCommandPool.hpp"

#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

namespace zt::gl
{
	vk::CommandPoolCreateInfo CommandPool::createCommandPoolCreateInfo(uint32_t queueFamilyIndex) const
	{
		vk::CommandPoolCreateInfo createInfo;
		createInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
		createInfo.queueFamilyIndex = queueFamilyIndex;

		return createInfo;
	}

	void CommandPool::create(const Device& device, uint32_t queueFamilyIndex)
	{
		vk::CommandPoolCreateInfo createInfo = createCommandPoolCreateInfo(queueFamilyIndex);
		vk::raii::CommandPool tempCommandPool{ device.getInternal(), createInfo };
		internal.swap(tempCommandPool);
		tempCommandPool.release();
	}

}
