#include "Zinet/GraphicLayer/ZtGLTextureRegion.hpp"

namespace zt::gl
{

	TextureRegion TextureRegion::toShaderTextureRegion(const Vector2f& textureSize) const
	{
		TextureRegion result = *this;
		result.offset.x /= textureSize.x;
		result.offset.y /= textureSize.y;
		result.size.x /= textureSize.x;
		result.size.y /= textureSize.y;

		return result;
	}

}