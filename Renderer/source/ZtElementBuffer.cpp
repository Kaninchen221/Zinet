#include "Zinet/Renderer/ZtElementBuffer.h"

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

GLuint ZtElementBuffer::GetID() const
{
	return ID;
}

void ZtElementBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
	ID = InvalidID;
}
