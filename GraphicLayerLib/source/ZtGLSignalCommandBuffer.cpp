#include "Zinet/GraphicLayer/ZtGLSignalCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

namespace zt::gl
{
	void SignalCommandBuffer::create(const RendererContext& rendererContext)
	{
		allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
		fence.create(rendererContext.getDevice(), fence.createUnsignaledFenceCreateInfo());
	}

	bool SignalCommandBuffer::isReady() const
	{
		const auto fenceStatus = fence.getStatus();
		if (fenceStatus == vk::Result::eSuccess)
			return true;

		return false;
	}

}
