#pragma once

#include "Zinet/GraphicLayer/ZtGLTextureRegion.hpp"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class TextureRegionTests : public ::testing::Test
	{
	protected:

		TextureRegion textureRegion
		{
			.offset = Vector2f{ 64.f, 64.f },
			.size = Vector2f{ 32.f, 32.f }
		};

	};

	TEST_F(TextureRegionTests, toShaderTextureRegion)
	{
		Vector2f textureSize{ 512.f, 512.f };
		TextureRegion shaderTextureRegion = textureRegion.toShaderTextureRegion(textureSize);

		Vector2f expectedOffset = { 0.125f, 0.125f };
		Vector2f expectedSize = { 0.0625f, 0.0625f };

		ASSERT_EQ(shaderTextureRegion.offset, expectedOffset);
		ASSERT_EQ(shaderTextureRegion.size, expectedSize);
	}

}
