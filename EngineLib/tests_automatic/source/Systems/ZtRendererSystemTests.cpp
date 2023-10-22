#pragma once

#include "Zinet/Engine/Systems/ZtRendererSystem.h"

#include "Zinet/Core/ZtTypeTraits.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class RendererSystemSimpleTests : public ::testing::Test
	{
	protected:

		RendererSystem rendererSystem;

		static_assert(std::is_default_constructible_v<RendererSystem>);
		static_assert(!std::is_copy_constructible_v<RendererSystem>);
		static_assert(!std::is_copy_assignable_v<RendererSystem>);
		static_assert(std::is_move_constructible_v<RendererSystem>);
		static_assert(std::is_move_assignable_v<RendererSystem>);
		static_assert(std::is_destructible_v<RendererSystem>);

		static_assert(std::is_base_of_v<ecs::System<DrawableComponent>, RendererSystem>);

		static_assert(std::is_same_v<RendererSystem::BaseT, ecs::System<DrawableComponent>>);
	};

	TEST_F(RendererSystemSimpleTests, GetRenderer)
	{
		bool result = core::TestGetters<gl::Renderer, RendererSystem>(&RendererSystem::getRenderer, &RendererSystem::getRenderer, rendererSystem);
		ASSERT_TRUE(result); 
	}

	TEST_F(RendererSystemSimpleTests, Initialize)
	{
		bool result = rendererSystem.initialize();
		EXPECT_TRUE(result);
	}

	TEST_F(RendererSystemSimpleTests, UpdateFunctions)
	{
		bool result = rendererSystem.initialize();
		ASSERT_TRUE(result);

		core::Time timeElapsed;
		rendererSystem.preUpdate(timeElapsed);
		rendererSystem.update(timeElapsed);
		rendererSystem.postUpdate(timeElapsed);
	}
}
