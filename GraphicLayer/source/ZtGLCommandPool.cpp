#include "Zinet/GraphicLayer/ZtGLCommandPool.h"

#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	CommandPool::CommandPool()
	{
	}

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
		internal = std::move(vk::raii::CommandPool{ device.getInternal(), createInfo });
	}

}
