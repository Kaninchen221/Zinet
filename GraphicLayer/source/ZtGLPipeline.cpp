#include "Zinet/GraphicLayer/ZtGLPipeline.h"

#include "Zinet/GraphicLayer/ZtGLPipelineLayout.h"
#include "Zinet/GraphicLayer/ZtGLDevice.h"

namespace zt::gl
{

	void Pipeline::create(Device& device, vk::GraphicsPipelineCreateInfo createInfo)
	{
		vk::raii::Pipeline vkRaiiPipeline{ device.getInternal(), nullptr, createInfo };
		vk::Result result = vkRaiiPipeline.getConstructorSuccessCode();
		if (result != vk::Result::eSuccess)
		{
			Logger->error("Create Pipeline return non success vk::Result");
		}

		internal = std::move(vkRaiiPipeline);
	}
}