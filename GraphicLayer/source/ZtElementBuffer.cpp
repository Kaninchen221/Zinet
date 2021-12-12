#include "Zinet/GraphicLayer/ZtElementBuffer.h"

namespace zt::gl
{

	ElementBuffer::~ElementBuffer() noexcept
	{
		if (iD != InvalidID)
		{
			deleteResource();
		}
	}

	void ElementBuffer::generate()
	{

	}

	void ElementBuffer::bind()
	{

	}

	void ElementBuffer::unbind()
	{

	}

	void ElementBuffer::deleteResource()
	{

	}

}