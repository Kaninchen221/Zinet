#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

	vk::raii::Context& Context::getInternal()
	{
		return internal;
	}

}