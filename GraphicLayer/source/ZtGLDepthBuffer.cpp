#include "Zinet/GraphicLayer/ZtGLDepthBuffer.h"

namespace zt::gl
{

	vk::Format DepthBuffer::findSupportedFormat([[maybe_unused]] const std::vector<vk::Format>& candidates, [[maybe_unused]] vk::ImageTiling imageTiling, [[maybe_unused]] vk::FormatFeatureFlags formatFeatureFlags) const
	{
		return {};
	}

}