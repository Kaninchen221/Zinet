#pragma once

#include "Zinet/GraphicLayer/ZtKeyboard.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class ZtKeyboardTests : public ::testing::Test
	{
	protected:

		Keyboard keyboard;

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(ZtKeyboardTests, SetWindowTest)
	{
		Window expectedWindow{};
		expectedWindow.create();
		keyboard.setWindow(&expectedWindow);
		const Window* actualWindow = keyboard.getWindow();

		ASSERT_EQ(actualWindow, &expectedWindow);
	}

	TEST_F(ZtKeyboardTests, GetWindowTest)
	{
		const Window* window = keyboard.getWindow();

		ASSERT_EQ(window, nullptr);
	}

	TEST_F(ZtKeyboardTests, IsPressedTest)
	{
		Window window;
		window.create();
		Event* event = window.getEvent();
		Keyboard* keyboard = event->getKeyboard();
		bool isPressed = keyboard->isPressed(KeyboardKey::F4);

		ASSERT_FALSE(isPressed);
	}

	TEST_F(ZtKeyboardTests, IsReleasedTest)
	{
		Window window;
		window.create();
		Event* event = window.getEvent();
		Keyboard* keyboard = event->getKeyboard();
		bool isReleased = keyboard->isReleased(KeyboardKey::F2);

		ASSERT_TRUE(isReleased);
	}

	TEST_F(ZtKeyboardTests, SetMaximumRememberedEventsTest)
	{
		size_t expectedMaximumRememberedEvents = 9u;
		keyboard.setMaximumRememberedEvents(expectedMaximumRememberedEvents);
		size_t actualMaximumRememberedEvents = keyboard.getMaximumRememberedEvents();

		ASSERT_EQ(expectedMaximumRememberedEvents, actualMaximumRememberedEvents);

		const std::vector<KeyboardEvent>& events = keyboard.getEvents();
		size_t actualEventsCount = events.size();
		size_t expectedEventsCount = expectedMaximumRememberedEvents;

		ASSERT_EQ(actualEventsCount, expectedEventsCount);
	}

}