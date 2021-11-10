#pragma once

#include "Zinet/GraphicLayer/ZtKeyboard.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtKeyboardTests : public ::testing::Test
{
protected:

	ZtKeyboard Keyboard;

};

TEST_F(ZtKeyboardTests, SetWindowTest)
{
	ZtWindow ExpectedWindow{};
	ExpectedWindow.CreateWindow();
	Keyboard.SetWindow(&ExpectedWindow);
	const ZtWindow* ActualWindow = Keyboard.GetWindow();

	ASSERT_EQ(ActualWindow, &ExpectedWindow);
}

TEST_F(ZtKeyboardTests, GetWindowTest)
{
	const ZtWindow* Window = Keyboard.GetWindow();

	ASSERT_EQ(Window, nullptr);
}

TEST_F(ZtKeyboardTests, IsPressedTest)
{
	ZtWindow Window;
	Window.CreateWindow();
	ZtEvent* Event = Window.GetEvent();
	ZtKeyboard* Keyboard = Event->GetKeyboard();
	bool IsPressed = Keyboard->IsPressed(ZtKeyboardKey::F4);

	ASSERT_FALSE(IsPressed);
}

TEST_F(ZtKeyboardTests, IsReleasedTest)
{
	ZtWindow Window;
	Window.CreateWindow();
	ZtEvent* Event = Window.GetEvent();
	ZtKeyboard* Keyboard = Event->GetKeyboard();
	bool IsReleased = Keyboard->IsReleased(ZtKeyboardKey::F2);

	ASSERT_TRUE(IsReleased);
}

TEST_F(ZtKeyboardTests, SetMaximumRememberedEventsTest)
{
	ZtKeyboard Keyboard;
	ZtSize ExpectedMaximumRememberedEvents = 9u;
	Keyboard.SetMaximumRememberedEvents(ExpectedMaximumRememberedEvents);
	size_t ActualMaximumRememberedEvents = Keyboard.GetMaximumRememberedEvents();

	ASSERT_EQ(ExpectedMaximumRememberedEvents, ActualMaximumRememberedEvents);

	const std::vector<ZtKeyboardEvent>& Events = Keyboard.GetEvents();
	size_t ActualEventsCount = Events.size();
	size_t ExpectedEventsCount = ExpectedMaximumRememberedEvents;

	ASSERT_EQ(ActualEventsCount, ExpectedEventsCount);
}