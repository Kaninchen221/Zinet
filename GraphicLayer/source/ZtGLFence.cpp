#include "Zinet/GraphicLayer/ZtGLFence.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{
	Fence::Fence()
		: internal{ std::nullptr_t{} }
	{
	}

	vk::raii::Fence& Fence::getInternal()
	{
		return internal;
	}

	vk::FenceCreateInfo Fence::createFenceCreateInfo()
	{
		vk::FenceCreateInfo createInfo{};

		return createInfo;
	}

	void Fence::createUnsignaled(Device& device)
	{
		vk::FenceCreateInfo createInfo = createFenceCreateInfo();
		internal = std::move(vk::raii::Fence{ device.getInternal(), createInfo });
	}

	void Fence::createSignaled(Device& device)
	{
		vk::FenceCreateInfo createInfo = createFenceCreateInfo();
		createInfo.flags = vk::FenceCreateFlagBits::eSignaled;

		internal = std::move(vk::raii::Fence{ device.getInternal(), createInfo });
	}

	vk::Result Fence::getStatus() const
	{
		return internal.getStatus();
	}

}
