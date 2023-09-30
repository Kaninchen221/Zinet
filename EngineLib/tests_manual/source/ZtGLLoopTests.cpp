#pragma once

#include "Zinet/Core/ZtLogger.h"

#include <gtest/gtest.h>

#include "Zinet/Engine/ZtLoop.h"

namespace zt::engine::tests
{

	class LoopTests : public ::testing::Test
	{
	public:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("LoopTests");

		Loop loop;

	};
	
	TEST_F(LoopTests, start)
	{
		wd::GLFW::UnhideWindow();

		loop.initialize();
		loop.start();
		loop.deinitialize();
	}

}