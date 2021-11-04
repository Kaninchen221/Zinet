#pragma once

#include "Zinet/GraphicLayer/ZtEvent.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtEventTests : public ::testing::Test
{
protected:

	ZtEvent Event{};

};

TEST_F(ZtEventTests, SetWindowTest)
{
	ZtWindow ExpectedWindow;
	ExpectedWindow.CreateWindow();
	Event.SetWindow(&ExpectedWindow);
	const ZtWindow* ActualWindow = Event.GetWindow();

	ASSERT_EQ(&ExpectedWindow, ActualWindow);
}

TEST_F(ZtEventTests, GetWindowTest)
{
	const ZtWindow* Window = Event.GetWindow();

	ASSERT_EQ(Window, nullptr);
}

TEST_F(ZtEventTests, PollEventsTest)
{
	Event.PollEvents();
}

TEST_F(ZtEventTests, GetKeyboardTest)
{
	ZtKeyboard* Keyboard = Event.GetKeyboard();
}