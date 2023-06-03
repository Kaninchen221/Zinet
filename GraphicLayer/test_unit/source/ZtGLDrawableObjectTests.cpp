#pragma once

#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"

#include <gtest/gtest.h>

namespace zt::gl
{
	class Texture;
}

namespace zt::gl::tests
{

	class DrawableObjectTests : public ::testing::Test
	{
	protected:

		static_assert(!std::is_default_constructible_v<DrawableObject>);

		class TestObject : public DrawableObject
		{
			DrawInfo createDrawInfo([[maybe_unused]] RendererContext& rendererContext) const override { return {}; }

			const Transform& getTransform() const override { return transform; }

		private:

			Transform transform;
			UniformBuffer uniformBuffer;

		};

		TestObject testObject;
	};

	TEST_F(DrawableObjectTests, Pass)
	{

	}

}
