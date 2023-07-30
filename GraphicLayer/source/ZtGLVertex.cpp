#include "Zinet/GraphicLayer/ZtGLVertex.h"

#include <glm/vector_relational.hpp>

namespace zt::gl
{

	Vertex::Vertex(const glm::vec3& newPosition, const glm::vec4& newColor, const glm::vec2& newTextureCoordinates)
		: position(newPosition),
		color(newColor),
		textureCoordinates(newTextureCoordinates)
	{}

	bool Vertex::operator==(const Vertex& other) const
	{
		bool equal = glm::all(glm::equal(position, other.position)) &&
			glm::all(glm::equal(color, other.color)) &&
			glm::all(glm::equal(textureCoordinates, other.textureCoordinates));

		return equal;
	}

	glm::vec3 Vertex::getPosition() const
	{
		return position;
	}

	void Vertex::setPosition(const glm::vec3& newPosition)
	{
		position = newPosition;
	}

	std::size_t Vertex::GetOffsetToPosition()
	{
		return 0;
	}

	glm::vec4 Vertex::getColor() const
	{
		return color;
	}

	void Vertex::setColor(const glm::vec4& newColor)
	{
		color = newColor;
	}

	std::size_t Vertex::GetOffsetToColor()
	{
		return sizeof(decltype(position));
	}

	glm::vec2 Vertex::getTextureCoordinates() const
	{
		return textureCoordinates;
	}

	void Vertex::setTextureCoordinates(const glm::vec2& newTextureCoordinates)
	{
		textureCoordinates = newTextureCoordinates;
	}

	std::size_t Vertex::GetOffsetToTextureCoordinates()
	{
		return sizeof(decltype(position)) + sizeof(decltype(color));
	}

	vk::VertexInputBindingDescription Vertex::CreateInputBindingDescription()
	{
		vk::VertexInputBindingDescription vertexInputBindingDescription{};
		vertexInputBindingDescription.binding = 0;
		vertexInputBindingDescription.stride = sizeof(Vertex);
		vertexInputBindingDescription.inputRate = vk::VertexInputRate::eVertex;

		return vertexInputBindingDescription;
	}

	std::vector<vk::VertexInputBindingDescription> Vertex::GetInputBindingDescriptions()
	{
		return
		{
			CreateInputBindingDescription()
		};
	}

	vk::VertexInputAttributeDescription Vertex::CreatePositionInputAttributeDescription()
	{
		vk::VertexInputAttributeDescription positionInputAttributeDescription;
		positionInputAttributeDescription.binding = 0;
		positionInputAttributeDescription.location = 0;
		positionInputAttributeDescription.format = vk::Format::eR32G32B32Sfloat;
		positionInputAttributeDescription.offset = 0;

		return positionInputAttributeDescription;
	}

	vk::VertexInputAttributeDescription Vertex::CreateColorInputAttributeDescription()
	{
		vk::VertexInputAttributeDescription colorInputAttributeDescription;
		colorInputAttributeDescription.binding = 0;
		colorInputAttributeDescription.location = 1;
		colorInputAttributeDescription.format = vk::Format::eR32G32B32A32Sfloat;
		colorInputAttributeDescription.offset = sizeof(position);

		return colorInputAttributeDescription;
	}

	vk::VertexInputAttributeDescription Vertex::CreateTextureCoordinatesInputAttributeDescription()
	{
		vk::VertexInputAttributeDescription textureCoordinatesInputAttributeDescription;
		textureCoordinatesInputAttributeDescription.binding = 0;
		textureCoordinatesInputAttributeDescription.location = 2;
		textureCoordinatesInputAttributeDescription.format = vk::Format::eR32G32Sfloat;
		textureCoordinatesInputAttributeDescription.offset = sizeof(position) + sizeof(color);

		return textureCoordinatesInputAttributeDescription;
	}

	std::vector<vk::VertexInputAttributeDescription> Vertex::GetInputAttributeDescriptions()
	{
		return
		{
			CreatePositionInputAttributeDescription(),
			CreateColorInputAttributeDescription(),
			CreateTextureCoordinatesInputAttributeDescription(),
		};
	}

}