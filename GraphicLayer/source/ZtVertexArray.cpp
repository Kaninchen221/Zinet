#include "Zinet/GraphicLayer/ZtVertexArray.h"

namespace zt::gl
{

	VertexArray::~VertexArray() noexcept
	{
		if (iD != InvalidID)
		{
			deleteResource();
		}
	}

	void VertexArray::generate()
	{

	}

	void VertexArray::bind()
	{

	}

	void VertexArray::unbind()
	{

	}

	void VertexArray::deleteResource()
	{
		iD = InvalidID;
	}

}