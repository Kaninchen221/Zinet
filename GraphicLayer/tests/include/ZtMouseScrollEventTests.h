#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"

#include "gtest/gtest.h"

class ZtMouseTests : public ::testing::Test
{
protected:

	ZtMouse Mouse;

};

TEST_F(ZtMouseTests, SetWindowTest)
{
	ZtWindow ExpectedWindow;
	ExpectedWindow.CreateWindow();
	Mouse.SetWindow(&ExpectedWindow);
	const ZtWindow* ActualWindow = Mouse.GetWindow();

	ASSERT_EQ(&ExpectedWindow, ActualWindow);
}

TEST_F(ZtMouseTests, GetWindowTest)
{
	const ZtWindow* ActualWindow = Mouse.GetWindow();

	ASSERT_EQ(ActualWindow, nullptr);
}

TEST_F(ZtMouseTests, GetButtonsEventsTest)
{
	const std::vector<ZtMouseButtonEvent>& ButtonsEvents = Mouse.GetButtonsEvents();
}

TEST_F(ZtMouseTests, SetMaximumRememberedButtonsEventsTest)
{
	size_t ExpectedMaximumRememberedButtonsEvents = 4u;
	Mouse.SetMaximumRememberedButtonsEvents(ExpectedMaximumRememberedButtonsEvents);
	size_t ActualMaximumRememberedButtonsEvents = Mouse.GetMaximumRememberedButtonsEvents();

	ASSERT_EQ(ExpectedMaximumRememberedButtonsEvents, ActualMaximumRememberedButtonsEvents);

	ActualMaximumRememberedButtonsEvents = Mouse.GetButtonsEvents().size();

	ASSERT_EQ(ExpectedMaximumRememberedButtonsEvents, ActualMaximumRememberedButtonsEvents);
}

TEST_F(ZtMouseTests, ButtonCallbackTest)
{
	ZtWindow Window;
	Window.CreateWindow();
	ZtMouseButtonEvent ExpectedButtonEvent{};
	ZtMouse::ButtonCallback(Window.GetInternalWindow(), static_cast<int>(ExpectedButtonEvent.Button), static_cast<int>(ExpectedButtonEvent.Type), 0);
	const std::vector<ZtMouseButtonEvent>& ButtonsEvents = Mouse.GetButtonsEvents();
	size_t ActualButtonsEventsCount = ButtonsEvents.size();
	size_t ExpectedButtonsEventsCount = 1u;

	ASSERT_EQ(ActualButtonsEventsCount, ExpectedButtonsEventsCount);

	ZtMouseButtonEvent ActualButtonEvent = ButtonsEvents[0];
	ASSERT_EQ(ExpectedButtonEvent, ActualButtonEvent);
}

TEST_F(ZtMouseTests, PositionCallbackTest)
{
	ZtMouse::PositionCallback((GLFWwindow*)nullptr, (double)0, (double)0);
	const std::vector<ZtMousePositionEvent>& Positions = Mouse.GetPositionEvents();
	size_t ActualPositionsCount = Positions.size();
	size_t ExpectedPositionsCount = 1u;

	ASSERT_EQ(ActualPositionsCount, ExpectedPositionsCount);
}

TEST_F(ZtMouseTests, GetPositionEventsTest)
{
	const std::vector<ZtMousePositionEvent>& Positions = Mouse.GetPositionEvents();
}