#include "Zinet/GraphicLayer/ZtVertexArray.h"

namespace zt::gl
{

	VertexArray::~VertexArray() noexcept
	{
		if (ID != InvalidID)
		{
			Delete();
		}
	}

	void VertexArray::Generate()
	{

	}

	void VertexArray::Bind()
	{

	}

	void VertexArray::Unbind()
	{

	}

	void VertexArray::Delete()
	{
		ID = InvalidID;
	}

}