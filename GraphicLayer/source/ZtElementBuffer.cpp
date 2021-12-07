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

}

void ZtElementBuffer::Bind()
{

}

void ZtElementBuffer::Unbind()
{

}

void ZtElementBuffer::Delete()
{

}
