#include "Zinet/GraphicLayer/ZtGLContext.h"

namespace zt::gl
{

	vk::raii::Context& Context::getInternal()
	{
		return internal;
	}

	vk::raii::Context* Context::operator->()
	{
		return &internal;
	}

}