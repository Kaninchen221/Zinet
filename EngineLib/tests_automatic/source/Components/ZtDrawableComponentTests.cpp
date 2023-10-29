#pragma once

#include "Zinet/Engine/ZtSprite.h"
#include "Zinet/Engine/Components/ZtDrawableComponent.h"

#include "Zinet/Core/ZtTypeTraits.h"

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

	TEST_F(DrawableComponentSimpleTests, GetDrawInfo)
	{
		typedef gl::DrawInfo (DrawableComponent::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&DrawableComponent::getDrawInfo));

		[[maybe_unused]] auto drawInfo = drawableComponent.getDrawInfo();
	}

	TEST_F(DrawableComponentSimpleTests, GetRenderStates)
	{
		typedef gl::RenderStates (DrawableComponent::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&DrawableComponent::getRenderStates));

		[[maybe_unused]] auto renderStates = drawableComponent.getRenderStates();
	}

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
}
