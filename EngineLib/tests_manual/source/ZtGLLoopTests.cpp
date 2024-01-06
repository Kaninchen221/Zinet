#pragma once

#include "Zinet/Core/ZtLogger.hpp"

#include <gtest/gtest.h>

#include "Zinet/Engine/ZtLoop.hpp"

namespace zt::engine::tests
{

	class LoopTests : public ::testing::Test
	{
	public:

		inline static core::ConsoleLogger Logger = core::ConsoleLogger::Create("LoopTests");

		Loop loop;

	};
	
// 	TEST_F(LoopTests, start)
// 	{
// 		wd::GLFW::UnhideWindow();
// 
// 		loop.initialize();
// 		loop.start();
// 		loop.deinitialize();
// 	}

}