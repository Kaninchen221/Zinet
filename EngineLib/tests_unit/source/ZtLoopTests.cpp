#pragma once

#include "Zinet/Engine/ZtLoop.h"

#include "Zinet/Core/ZtTypeTraits.h"
#include "Zinet/Core/ZtTime.h"

#include <gtest/gtest.h>

namespace zt::engine::tests
{

	class LoopTests : public ::testing::Test
	{
	protected:

		Loop loop;
	};

	TEST_F(LoopTests, GetRenderer)
	{
		auto result = core::TestGetters<gl::Renderer, Loop>(&Loop::getRenderer, &Loop::getRenderer, loop);
		EXPECT_TRUE(result);
	}

	TEST_F(LoopTests, GetImgui)
	{
		auto result = core::TestGetters<gl::Imgui, Loop>(&Loop::getImgui, &Loop::getImgui, loop);
		EXPECT_TRUE(result);
	}

	TEST_F(LoopTests, Initialize)
	{
		loop.initialize();
	}

	TEST_F(LoopTests, Deinitialize)
	{
		loop.initialize();
		loop.deinitialize();
	}

	TEST_F(LoopTests, Tick)
	{
		const core::Time elapsedTime;

		loop.initialize();
		loop.tick(elapsedTime);
		loop.deinitialize();
	}
}
