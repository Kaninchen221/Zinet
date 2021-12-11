#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayer.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace zt::gl
{

	class ZINET_GRAPHIC_LAYER_API Vertex
	{

	public:

		Vertex() = default;
		Vertex(const Vertex& Other) = default;
		Vertex(Vertex&& Other) = default;
		Vertex(const glm::vec3& NewPosition, const glm::vec4& NewColor, const glm::vec2& NewTextureCoordinates);

		Vertex& operator = (const Vertex& Other) = default;
		Vertex& operator = (Vertex&& Other) = default;

		~Vertex() noexcept = default;

		glm::vec3 GetPosition() const;

		void SetPosition(const glm::vec3& NewPosition);

		static std::size_t GetOffsetToPosition();

		glm::vec4 GetColor() const;

		void SetColor(const glm::vec4& NewColor);

		static std::size_t GetOffsetToColor();

		glm::vec2 GetTextureCoordinates() const;

		void SetTextureCoordinates(const glm::vec2& NewTextureCoordinates);

		static std::size_t GetOffsetToTextureCoordinates();

	protected:

		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoordinates;

	};

}