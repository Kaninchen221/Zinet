#pragma once

#include "Zinet/GraphicLayer/ZtGLDrawableObject.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class DrawableObjectTests : public ::testing::Test
	{
	protected:

		static_assert(!std::is_default_constructible_v<DrawableObject>);

		class TestObject : public DrawableObject
		{
			VertexBuffer vertexBuffer;
			IndexBuffer indexBuffer;

			DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };

			const DrawInfo& getDrawInfo() const override { return drawInfo; }

			void createDrawInfo() override {}

		};

		TestObject testObject;
	};

	TEST_F(DrawableObjectTests, Pass)
	{

	}

}
