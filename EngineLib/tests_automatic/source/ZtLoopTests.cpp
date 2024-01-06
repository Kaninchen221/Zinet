#pragma once

#include "Zinet/Engine/ZtLoop.hpp"

#include "Zinet/Core/ZtTypeTraits.hpp"
#include "Zinet/Core/ZtTime.hpp"

#include <gtest/gtest.h>

#include <future>

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

	TEST_F(LoopTests, step)
	{
		const core::Time elapsedTime;

		loop.initialize();
		loop.step(elapsedTime);
		loop.deinitialize();
	}

	TEST_F(LoopTests, shouldTick)
	{
		bool shouldTick = loop.shouldTick();
		EXPECT_FALSE(shouldTick);

		loop.initialize();
		shouldTick = loop.shouldTick();
		EXPECT_TRUE(shouldTick);
	}

	TEST_F(LoopTests, requestTickEnd)
	{
		loop.initialize();
		bool shouldTick = loop.shouldTick();
		EXPECT_TRUE(shouldTick);

		loop.setRequestTickEnd(true);
		shouldTick = loop.shouldTick();
		EXPECT_FALSE(shouldTick);
	}

	TEST_F(LoopTests, getLastTickElapsedTime)
	{
		typedef const core::Time& (Loop::* ExpectedFunction)() const;
		static_assert(core::IsFunctionEqual<ExpectedFunction>(&Loop::getLastTickElapsedTime));

		[[maybe_unused]] const core::Time& elapsedTime = loop.getLastTickElapsedTime();
	}

	TEST_F(LoopTests, start)
	{
		loop.initialize();
		auto asyncResult = std::async(std::launch::async, [&]() 
		{ 
			while (true)
			{
				if (loop.getLastTickElapsedTime() != core::Time{})
				{
					loop.setRequestTickEnd(true);
					break;
				}
			}
		}
		);
		loop.start();
		loop.deinitialize();
	}
}
