#include "Zinet/GraphicLayer/ZtVertex.h"

ZtVertex::ZtVertex(const glm::vec3& NewPosition, const glm::vec4& NewColor, const glm::vec2& NewTextureCoordinates)
	: Position(NewPosition),
	Color(NewColor),
	TextureCoordinates(NewTextureCoordinates)
{}

glm::vec3 ZtVertex::GetPosition() const
{
	return Position;
}

void ZtVertex::SetPosition(const glm::vec3& NewPosition)
{
	Position = NewPosition;
}

std::size_t ZtVertex::GetOffsetToPosition()
{
	return 0;
}

glm::vec4 ZtVertex::GetColor() const
{
	return Color;
}

void ZtVertex::SetColor(const glm::vec4& NewColor)
{
	Color = NewColor;
}

std::size_t ZtVertex::GetOffsetToColor()
{
	return sizeof(decltype(Position));
}

glm::vec2 ZtVertex::GetTextureCoordinates() const
{
	return TextureCoordinates;
}

void ZtVertex::SetTextureCoordinates(const glm::vec2& NewTextureCoordinates)
{
	TextureCoordinates = NewTextureCoordinates;
}

std::size_t ZtVertex::GetOffsetToTextureCoordinates()
{
	return sizeof(decltype(Position)) + sizeof(decltype(Color));
}
