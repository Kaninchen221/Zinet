#include "Zinet/Renderer/ZtVertex.h"

ZtVertex::ZtVertex(const glm::vec3& NewPosition)
	: Position(NewPosition)
{}

glm::vec3 ZtVertex::GetPosition() const
{
	return Position;
}

void ZtVertex::SetPosition(const glm::vec3& NewPosition)
{
	Position = NewPosition;
}
