#pragma once

#include "Zinet/GraphicLayer/ZtGLDrawable2DBase.h"
#include "Zinet/GraphicLayer/ZtGLRendererContext.h"
#include "Zinet/GraphicLayer/ZtGLTextureRegion.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

#include <filesystem>

namespace zt::gl::tests
{
	class TestDrawable2DBaseClass : public Drawable2DBase
	{
		DrawInfo createDrawInfo(RendererContext& rendererContext) const override { return std::move(DrawInfo{}); }
		
		const Transform& getTransform() const { return transform; }
		void setTransform(const Transform& newTransform) override { transform = newTransform; }

		std::vector<RenderStates::Descriptor> createRenderStatesDescriptors() const override { return {}; }

		Transform transform;
	};

	class Drawable2DBaseSimpleTests : public ::testing::Test
	{
	protected:

		static_assert(std::is_abstract_v<Drawable2DBase>);

		TestDrawable2DBaseClass testObject;
	};

	TEST_F(Drawable2DBaseSimpleTests, GetDefaultIndices)
	{
		std::array<std::uint16_t, 6u> actual = Drawable2DBase::GetDefaultIndices();
		std::array<std::uint16_t, 6u> expected{ 0u, 1u, 2u, 2u, 3u, 0u };

		EXPECT_EQ(actual, expected);
	}

	TEST_F(Drawable2DBaseSimpleTests, GetDefaultVerticesCount)
	{
		size_t actual = Drawable2DBase::GetDefaultVerticesCount();
		size_t expected = 4u;

		EXPECT_EQ(actual, expected);
	}

	TEST_F(Drawable2DBaseSimpleTests, GetAbsoluteSize)
	{
		Vector2ui absoluteSize = testObject.getAbsoluteSize();
		Vector2ui expected = Vector2ui{ 1u, 1u };

		EXPECT_EQ(absoluteSize, expected);
	}

	class Drawable2DBaseTests : public ::testing::Test
	{
	protected:

		RendererContext rendererContext;
		TestDrawable2DBaseClass testObject;

		void SetUp() override
		{
			GLFW::Init();
			rendererContext.initialize();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(Drawable2DBaseTests, CreateIndexBuffer)
	{
		IndexBuffer indexBuffer;
		std::vector<std::uint16_t> indices{ 1u, 2u };
		testObject.createIndexBuffer(indexBuffer, indices, rendererContext);

		EXPECT_TRUE(indexBuffer.isValid());
	}

	TEST_F(Drawable2DBaseTests, CreateVertexBuffer)
	{
		VertexBuffer vertexBuffer;
		TextureRegion textureRegion;
		testObject.createVertexBuffer(vertexBuffer, textureRegion, rendererContext);

		EXPECT_TRUE(vertexBuffer.isValid());
	}
}
