#include "Zinet/GraphicLayer/ZtGLFence.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

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

	void Fence::create(const Device& device, const vk::FenceCreateInfo& createInfo)
	{
		vk::raii::Fence tempFence{ device.getInternal(), createInfo };
		internal.swap(tempFence);
		tempFence.release();
	}

	vk::Result Fence::getStatus() const
	{
		return internal.getStatus();
	}

}
