#pragma once

#include "Zinet/GraphicLayer/ZtGLShape2D.hpp"
#include "Zinet/GraphicLayer/ZtGLDrawableBase.hpp"
#include "Zinet/GraphicLayer/ZtGLRenderer.hpp"
#include "Zinet/GraphicLayer/ZtGLTexture.hpp"
#include "Zinet/GraphicLayer/ZtGLSampler.hpp"
#include "Zinet/GraphicLayer/ZtGLShader.hpp"

#include "Zinet/Window/ZtGLFW.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{

	class Shape2DTests : public ::testing::Test
	{
	protected:

		const inline static std::filesystem::path ContentPath = ZINET_CURRENT_PROJECT_ROOT_PATH "/test_files";

		Renderer renderer;
		Shape2D shape2D;
		std::vector<Shader> shaders;

		static_assert(std::is_base_of_v<Drawable2DBase, Shape2D>);
		static_assert(std::is_default_constructible_v<Shape2D>);

		static_assert(std::is_copy_constructible_v<Shape2D>);
		static_assert(std::is_copy_assignable_v<Shape2D>);

		static_assert(std::is_move_constructible_v<Shape2D>);
		static_assert(std::is_move_assignable_v<Shape2D>);

		static_assert(std::is_destructible_v<Shape2D>);

		void SetUp() override
		{
			wd::GLFW::Init(false);
			renderer.initialize();
			RendererContext& rendererContext = renderer.getRendererContext();

			shaders.emplace_back();
			shaders[0].setType(ShaderType::Vertex);
			shaders[0].loadFromFile((ContentPath / "shape2D.vert").string());
			shaders[0].compile();

			shaders.emplace_back();
			shaders[1].setType(ShaderType::Fragment);
			shaders[1].loadFromFile((ContentPath / "shape2D.frag").string());
			shaders[1].compile();

			shape2D.createDrawInfo(rendererContext);
		}

		void TearDown() override
		{
			wd::GLFW::Deinit();
		}
	};

	TEST_F(Shape2DTests, CreateDrawInfo)
	{
		DrawInfo drawInfo = shape2D.createDrawInfo(renderer.getRendererContext());

		EXPECT_TRUE(drawInfo.vertexBuffer.isValid());
		EXPECT_TRUE(drawInfo.indexBuffer.isValid());
		EXPECT_FALSE(drawInfo.indices.empty());
		EXPECT_FALSE(drawInfo.uniformBuffers.empty());
	}

	class Shape2DSimpleTests : public ::testing::Test
	{
	protected:

		Shape2D shape2D;
	};

	TEST_F(Shape2DSimpleTests, GetSetTransform)
	{
		typedef const Transform& (Shape2D::* ExpectedFunction)() const;
		static_assert(zt::core::IsFunctionEqual<ExpectedFunction>(&Shape2D::getTransform));

		Transform expected;
		expected.setTranslation({ 12.4f, 3.f, 1.f });
		expected.setScale({ 112.4f, 3.42f, 11.f });
		expected.setRotation({ 1.41f, 0.412f, 1.212f });
		shape2D.setTransform(expected);

		const Transform& actual = shape2D.getTransform();
		ASSERT_EQ(expected, actual);
	}

	TEST_F(Shape2DSimpleTests, GetAbsoluteSize)
	{
		Vector2ui actualAbsoluteSize = shape2D.getAbsoluteSize();
		Vector2ui expectedAboluteSize = Vector2ui{ 1u, 1u };
		ASSERT_EQ(actualAbsoluteSize, expectedAboluteSize);
	}

	TEST_F(Shape2DSimpleTests, Copy)
	{
		Transform transform;
		transform.setRotation({ 2.f, 1.f, 5.f });
		transform.setScale({ 1.f, 7.f, 2.f });
		transform.setTranslation({ 4.f, 6.f, 6.f });

		shape2D.setTransform(transform);

		Shape2D secondShape2D;
		secondShape2D = shape2D;

		EXPECT_EQ(shape2D.getTransform(), secondShape2D.getTransform());

		Shape2D thirdShape2D{ shape2D };

		EXPECT_EQ(shape2D.getTransform(), thirdShape2D.getTransform());
	}

	TEST_F(Shape2DSimpleTests, CreateRenderStatesDescriptors)
	{
		std::vector<RenderStates::Descriptor> descriptors = shape2D.createRenderStatesDescriptors();
		ASSERT_FALSE(descriptors.empty());
	}
}
