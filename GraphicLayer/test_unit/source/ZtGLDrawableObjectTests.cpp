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
			VertexBuffer vertexBuffer;
			IndexBuffer indexBuffer;

			DrawInfo drawInfo{ .vertexBuffer = vertexBuffer, .indexBuffer = indexBuffer };

			const DrawInfo& getDrawInfo() const override { return drawInfo; }

			void createDrawInfo([[maybe_unused]] std::span<Shader> shaders, [[maybe_unused]] const Texture& texture, [[maybe_unused]] const Sampler& sampler) override {}

			const Transform& getTransform() const override { return transform; }

		private:

			Transform transform;

		};

		TestObject testObject;
	};

	TEST_F(DrawableObjectTests, Pass)
	{

	}

}
