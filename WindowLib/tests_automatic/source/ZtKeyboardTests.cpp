#pragma once

#include "Zinet/Window/ZtKeyboard.h"
#include "Zinet/Window/ZtWindow.h"
#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::wd::tests
{

	class KeyboardTests : public ::testing::Test
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

	TEST_F(KeyboardTests, SetWindow)
	{
		Window expectedWindow{};
		expectedWindow.create();
		keyboard.setWindow(&expectedWindow);
		const Window* actualWindow = keyboard.getWindow();

		ASSERT_EQ(actualWindow, &expectedWindow);
	}

	TEST_F(KeyboardTests, GetWindow)
	{
		const Window* window = keyboard.getWindow();

		ASSERT_EQ(window, nullptr);
	}

	TEST(Keyboard, IsPressed)
	{
		GLFW::Init();

		Window window;
		window.create();
		Event* event = window.getEvent();
		Keyboard* keyboard = event->getKeyboard();
		ASSERT_NE(keyboard, nullptr);

		bool isPressed = keyboard->isPressed(KeyboardKey::F4);
		ASSERT_FALSE(isPressed);

		GLFW::Deinit();
	}

	TEST(Keyboard, IsReleased)
	{
		GLFW::Init();

		Window window;
		window.create();
		Event* event = window.getEvent();
		Keyboard* keyboard = event->getKeyboard();
		ASSERT_NE(keyboard, nullptr);

		bool isReleased = keyboard->isReleased(KeyboardKey::F2);
		ASSERT_TRUE(isReleased);

		GLFW::Deinit();
	}

	TEST_F(KeyboardTests, SetMaximumRememberedEvents)
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