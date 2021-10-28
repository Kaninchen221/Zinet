#include "Zinet/GraphicLayer/ZtElementBuffer.h"

ZtElementBuffer::~ZtElementBuffer() noexcept
{
	if (ID != InvalidID)
	{
		Delete();
	}
}

void ZtElementBuffer::Generate()
{
	glGenBuffers(1, &ID);
}

void ZtElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ZtElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
}

void ZtElementBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
	ID = InvalidID;
}
