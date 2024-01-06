#pragma once

#include "Zinet/GraphicLayer/ZtGraphicLayerConfig.hpp"
#include "Zinet/GraphicLayer/ZtGLVulkanObject.hpp"

#include "Zinet/Math/ZtVecTypes.hpp"

#include "Zinet/Core/ZtLogger.hpp"

namespace zt::gl
{

	struct ZINET_GRAPHIC_LAYER_API TextureRegion
	{
		Vector2f offset;
		Vector2f size;

		TextureRegion toShaderTextureRegion(const Vector2f& textureSize) const;

	};

	ZINET_GRAPHIC_LAYER_API inline bool operator == (const TextureRegion& first, const TextureRegion& second)
	{
		return first.offset == second.offset && first.size == second.size;
	}
}