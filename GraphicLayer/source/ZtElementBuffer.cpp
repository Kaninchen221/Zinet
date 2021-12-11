#include "Zinet/GraphicLayer/ZtElementBuffer.h"

namespace zt::gl
{

	ElementBuffer::~ElementBuffer() noexcept
	{
		if (ID != InvalidID)
		{
			Delete();
		}
	}

	void ElementBuffer::Generate()
	{

	}

	void ElementBuffer::Bind()
	{

	}

	void ElementBuffer::Unbind()
	{

	}

	void ElementBuffer::Delete()
	{

	}

}