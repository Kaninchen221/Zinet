#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

	const vk::raii::Context& Context::getInternal() const
	{
		return internal;
	}

}