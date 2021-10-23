#include "Zinet/Renderer/ZtVertexBuffer.h"

void ZtVertexBuffer::Generate()
{
	glGenBuffers(1, &ID);
}

void ZtVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void ZtVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0u);
}

GLuint ZtVertexBuffer::GetID() const
{
	return ID;
}

void ZtVertexBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
	ID = InvalidID;
}
