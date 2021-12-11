#pragma once

#include "Zinet/GraphicLayer/ZtKeyboard.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

namespace zt::gl::tests
{

	class ZtKeyboardTests : public ::testing::Test
	{
	protected:

		Keyboard keyboard;

	};

	TEST_F(ZtKeyboardTests, SetWindowTest)
	{
		Window ExpectedWindow{};
		ExpectedWindow.CreateWindow();
		keyboard.SetWindow(&ExpectedWindow);
		const Window* ActualWindow = keyboard.GetWindow();

		ASSERT_EQ(ActualWindow, &ExpectedWindow);
	}

	TEST_F(ZtKeyboardTests, GetWindowTest)
	{
		const Window* Window = keyboard.GetWindow();

		ASSERT_EQ(Window, nullptr);
	}

	TEST_F(ZtKeyboardTests, IsPressedTest)
	{
		Window Window;
		Window.CreateWindow();
		Event* Event = Window.GetEvent();
		Keyboard* keyboard = Event->GetKeyboard();
		bool IsPressed = keyboard->IsPressed(KeyboardKey::F4);

		ASSERT_FALSE(IsPressed);
	}

	TEST_F(ZtKeyboardTests, IsReleasedTest)
	{
		Window Window;
		Window.CreateWindow();
		Event* Event = Window.GetEvent();
		Keyboard* keyboard = Event->GetKeyboard();
		bool IsReleased = keyboard->IsReleased(KeyboardKey::F2);

		ASSERT_TRUE(IsReleased);
	}

	TEST_F(ZtKeyboardTests, SetMaximumRememberedEventsTest)
	{
		size_t ExpectedMaximumRememberedEvents = 9u;
		keyboard.SetMaximumRememberedEvents(ExpectedMaximumRememberedEvents);
		size_t ActualMaximumRememberedEvents = keyboard.GetMaximumRememberedEvents();

		ASSERT_EQ(ExpectedMaximumRememberedEvents, ActualMaximumRememberedEvents);

		const std::vector<KeyboardEvent>& events = keyboard.GetEvents();
		size_t ActualEventsCount = events.size();
		size_t ExpectedEventsCount = ExpectedMaximumRememberedEvents;

		ASSERT_EQ(ActualEventsCount, ExpectedEventsCount);
	}

}