#pragma once

#include "Zinet/Window/ZtEvent.h"
#include "Zinet/Window/ZtWindow.h"

#include <GLFW/glfw3.h>

#include <gtest/gtest.h>

namespace zt::wd::tests
{

	class EventTests : public ::testing::Test
	{
	protected:

		GLFW glfw;
		Window window;
		Event event{ window };

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(EventTests, SetWindow)
	{
 		window.create();
 		const Window* actualWindow = event.getWindow();
 
 		EXPECT_EQ(&window, actualWindow);
	}

	TEST_F(EventTests, GetWindow)
	{
		const Window* actualWindow = event.getWindow();
		EXPECT_EQ(actualWindow, &window);
	}

	TEST_F(EventTests, PollEvents)
	{
		event.pollEvents();
	}

	TEST_F(EventTests, GetKeyboard)
	{
		Keyboard* keyboard = event.getKeyboard();

		ASSERT_NE(keyboard, nullptr);
	}

	TEST_F(EventTests, GetMouse)
	{
		Mouse* mouse = event.getMouse();

		ASSERT_NE(mouse, nullptr);
	}

}