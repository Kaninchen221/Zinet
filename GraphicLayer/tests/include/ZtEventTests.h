#pragma once

#include "Zinet/GraphicLayer/ZtEvent.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtEventTests : public ::testing::Test
	{
	protected:

		Event Event{};

	};

	TEST_F(ZtEventTests, SetWindowTest)
	{
		Window ExpectedWindow;
		ExpectedWindow.CreateWindow();
		Event.SetWindow(&ExpectedWindow);
		const Window* ActualWindow = Event.GetWindow();

		ASSERT_EQ(&ExpectedWindow, ActualWindow);
	}

	TEST_F(ZtEventTests, GetWindowTest)
	{
		const Window* Window = Event.GetWindow();

		ASSERT_EQ(Window, nullptr);
	}

	TEST_F(ZtEventTests, PollEventsTest)
	{
		Event.PollEvents();
	}

	TEST_F(ZtEventTests, GetKeyboardTest)
	{
		Keyboard* Keyboard = Event.GetKeyboard();

		ASSERT_NE(Keyboard, nullptr);
	}

	TEST_F(ZtEventTests, GetMouseTest)
	{
		Mouse* Mouse = Event.GetMouse();

		ASSERT_NE(Mouse, nullptr);
	}

}