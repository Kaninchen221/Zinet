#include "Zinet/GraphicLayer/ZtGLSignalCommandBuffer.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

namespace zt::gl
{
	void SignalCommandBuffer::create(const RendererContext& rendererContext)
	{
		commandBuffer.allocateCommandBuffer(rendererContext.getDevice(), rendererContext.getCommandPool());
		fence.create(rendererContext.getDevice(), fence.createUnsignaledFenceCreateInfo());
	}
}
