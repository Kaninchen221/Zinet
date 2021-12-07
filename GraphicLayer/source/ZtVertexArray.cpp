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

}

void ZtVertexArray::Bind()
{

}

void ZtVertexArray::Unbind()
{

}

void ZtVertexArray::Delete()
{
	ID = InvalidID;
}
