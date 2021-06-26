#pragma once

#include "ZtCore.h"

#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/BlendMode.hpp"
#include "SFML/Graphics/Shader.hpp"

#include "plf_colony.h"

struct ZINET_CORE_API ZtRenderInfo
{
	const sf::Vertex* FirstVertexAddress;
	size_t VerticesCount;
	const sf::PrimitiveType& PrimitiveType;
	const sf::IntRect& TextureSourceRectangle;
	const sf::RenderStates& RenderStates;
};