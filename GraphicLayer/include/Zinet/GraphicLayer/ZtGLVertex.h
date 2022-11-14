#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Vertex
	{

	public:

		Vertex() = default;
		Vertex(const Vertex& other) = default;
		Vertex(Vertex&& other) = default;
		Vertex(const glm::vec3& newPosition, const glm::vec4& newColor, const glm::vec2& newTextureCoordinates);

		Vertex& operator = (const Vertex& other) = default;
		Vertex& operator = (Vertex&& other) = default;

		bool operator == (const Vertex& other) const;

		~Vertex() noexcept = default;

		glm::vec3 getPosition() const;

		void setPosition(const glm::vec3& newPosition);

		static std::size_t GetOffsetToPosition();

		glm::vec4 getColor() const;

		void setColor(const glm::vec4& newColor);

		static std::size_t GetOffsetToColor();

		glm::vec2 getTextureCoordinates() const;

		void setTextureCoordinates(const glm::vec2& newTextureCoordinates);

		static std::size_t GetOffsetToTextureCoordinates();

		static vk::VertexInputBindingDescription CreateInputBindingDescription();

		static vk::VertexInputAttributeDescription CreatePositionInputAttributeDescription();

		static vk::VertexInputAttributeDescription CreateColorInputAttributeDescription();

		static vk::VertexInputAttributeDescription CreateTextureCoordinatesInputAttributeDescription();

	protected:

		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 textureCoordinates;

	};

}