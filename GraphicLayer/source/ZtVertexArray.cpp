#include "Zinet/GraphicLayer/ZtVertexArray.h"

ZtVertexArray::~ZtVertexArray() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtVertexArray::Generate()
{
	glGenVertexArrays(1, &ID);
}

void ZtVertexArray::Bind()
{
	glBindVertexArray(ID);
}

void ZtVertexArray::Unbind()
{
	glBindVertexArray(InvalidID);
}

void ZtVertexArray::Delete()
{
	glDeleteVertexArrays(1, &ID);
	ID = InvalidID;
}
