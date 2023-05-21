#pragma once

#include "Zinet/GraphicLayer/ZtGLEvent.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class EventTests : public ::testing::Test
	{
	protected:

		Event event{};

	};

	TEST_F(EventTests, SetWindow)
	{
		GLFW::Init();

		Window expectedWindow;
		expectedWindow.create();
		event.setWindow(&expectedWindow);
		const Window* actualWindow = event.getWindow();

		ASSERT_EQ(&expectedWindow, actualWindow);

		GLFW::Deinit();
	}

	TEST_F(EventTests, GetWindow)
	{
		const Window* window = event.getWindow();

		ASSERT_EQ(window, nullptr);
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