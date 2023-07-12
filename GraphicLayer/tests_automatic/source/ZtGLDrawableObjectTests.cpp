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

			Vector2ui getAbsoluteSize() const override { return Vector2ui{ 1.f, 1.f }; }

		private:

			Transform transform;

		};

		TestObject testObject;
	};

	TEST_F(DrawableObjectTests, Pass)
	{

	}

}
