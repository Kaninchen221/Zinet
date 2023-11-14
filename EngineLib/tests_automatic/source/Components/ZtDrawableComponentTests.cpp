#pragma once

#include "Zinet/Engine/ZtSprite.h"
#include "Zinet/Engine/Components/ZtDrawableComponent.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include "Zinet/GraphicLayer/ZtGLRendererContext.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class DrawableComponentSimpleTests : public ::testing::Test
	{
	protected:

		DrawableComponent drawableComponent;

		static_assert(std::is_default_constructible_v<DrawableComponent>);
		static_assert(!std::is_copy_constructible_v<DrawableComponent>);
		static_assert(!std::is_copy_assignable_v<DrawableComponent>);
		static_assert(std::is_move_constructible_v<DrawableComponent>);
		static_assert(std::is_move_assignable_v<DrawableComponent>);
		static_assert(std::is_destructible_v<DrawableComponent>);

		static_assert(std::is_base_of_v<ecs::Component, DrawableComponent>);
	};

	TEST_F(DrawableComponentSimpleTests, CreateDrawInfo)
	{
		typedef gl::DrawInfo (DrawableComponent::* ExpectedFunction)(gl::RendererContext&) const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&DrawableComponent::createDrawInfo));

		gl::RendererContext rendererContext;
		[[maybe_unused]] auto drawInfo = drawableComponent.createDrawInfo(rendererContext);
	}

	TEST_F(DrawableComponentSimpleTests, CreateRenderStates)
	{
		typedef gl::RenderStates (DrawableComponent::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&DrawableComponent::createRenderStates));

		[[maybe_unused]] auto renderStates = drawableComponent.createRenderStates();
	}

	// Naive implementation
	TEST_F(DrawableComponentSimpleTests, Create)
	{
		drawableComponent.create<Sprite>();

		const gl::DrawableBase* validDrawable = drawableComponent.getDrawable();
		ASSERT_NE(validDrawable, nullptr);
	}

	TEST_F(DrawableComponentSimpleTests, GetDrawable)
	{
		const gl::DrawableBase* invalidDrawable = drawableComponent.getDrawable();
		ASSERT_EQ(invalidDrawable, nullptr);
	}

	TEST_F(DrawableComponentSimpleTests, IsDataValid)
	{
		bool isDataValid = drawableComponent.isDataValid();
		EXPECT_FALSE(isDataValid);

		drawableComponent.create<Sprite>();
		isDataValid = drawableComponent.isDataValid();
		EXPECT_TRUE(isDataValid);
	}

	TEST_F(DrawableComponentSimpleTests, GetShaders)
	{
		const std::vector<gl::Shader>& shaders = drawableComponent.getShaders();
		ASSERT_TRUE(shaders.empty());
	}

	// Naive implementation
	TEST_F(DrawableComponentSimpleTests, SetShaders)
	{
		const std::vector<gl::Shader>& expectedShaders = { gl::Shader{}, gl::Shader{} };
		drawableComponent.setShaders(expectedShaders);

		const std::vector<gl::Shader>& shaders = drawableComponent.getShaders();
		ASSERT_EQ(expectedShaders.size(), shaders.size());
	}
}
