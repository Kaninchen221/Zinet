#include "Zinet/GraphicLayer/ZtGLPipeline.hpp"

#include "Zinet/GraphicLayer/ZtGLPipelineLayout.hpp"
#include "Zinet/GraphicLayer/ZtGLDevice.hpp"

namespace zt::gl
{

	void Pipeline::create(Device& device, vk::GraphicsPipelineCreateInfo createInfo)
	{
		vk::raii::Pipeline tempPipeline{ device.getInternal(), nullptr, createInfo };
		vk::Result result = tempPipeline.getConstructorSuccessCode();
		if (result != vk::Result::eSuccess)
		{
			Logger->error("Create Pipeline return non success vk::Result");
		}

		internal.swap(tempPipeline);
		tempPipeline.release();
	}
}