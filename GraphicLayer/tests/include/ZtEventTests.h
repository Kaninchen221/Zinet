#pragma once

#include "Zinet/GraphicLayer/ZtEvent.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ZtEventTests : public ::testing::Test
	{
	protected:

		Event event{};

	};

	TEST_F(ZtEventTests, SetWindowTest)
	{
		Window expectedWindow;
		expectedWindow.create();
		event.setWindow(&expectedWindow);
		const Window* actualWindow = event.getWindow();

		ASSERT_EQ(&expectedWindow, actualWindow);
	}

	TEST_F(ZtEventTests, GetWindowTest)
	{
		const Window* window = event.getWindow();

		ASSERT_EQ(window, nullptr);
	}

	TEST_F(ZtEventTests, PollEventsTest)
	{
		event.pollEvents();
	}

	TEST_F(ZtEventTests, GetKeyboardTest)
	{
		Keyboard* keyboard = event.getKeyboard();

		ASSERT_NE(keyboard, nullptr);
	}

	TEST_F(ZtEventTests, GetMouseTest)
	{
		Mouse* mouse = event.getMouse();

		ASSERT_NE(mouse, nullptr);
	}

}