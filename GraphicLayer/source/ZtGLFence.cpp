#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	vk::FenceCreateInfo Fence::createSignaledFenceCreateInfo()
	{
		vk::FenceCreateInfo createInfo{};
		createInfo.flags = vk::FenceCreateFlagBits::eSignaled;

		return createInfo;
	}

	vk::FenceCreateInfo Fence::createUnsignaledFenceCreateInfo()
	{
		vk::FenceCreateInfo createInfo{};

		return createInfo;
	}

	void Fence::create(Device& device, const vk::FenceCreateInfo& createInfo)
	{
		internal = std::move(vk::raii::Fence{ device.getInternal(), createInfo });
	}

	vk::Result Fence::getStatus() const
	{
		return internal.getStatus();
	}

}
