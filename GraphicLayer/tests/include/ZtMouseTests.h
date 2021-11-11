#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"

#include "gtest/gtest.h"

#include "vec2.hpp"
#include "vector_relational.hpp"

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

TEST_F(ZtMouseTests, SetMaxRememberedButtonsEventsTest)
{
	size_t ExpectedMaxRememberedButtonsEvents = 4u;
	Mouse.SetMaxRememberedButtonsEvents(ExpectedMaxRememberedButtonsEvents);
	size_t ActualMaxRememberedButtonsEvents = Mouse.GetMaxRememberedButtonsEvents();

	ASSERT_EQ(ExpectedMaxRememberedButtonsEvents, ActualMaxRememberedButtonsEvents);

	ActualMaxRememberedButtonsEvents = Mouse.GetButtonsEvents().size();

	ASSERT_EQ(ExpectedMaxRememberedButtonsEvents, ActualMaxRememberedButtonsEvents);
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
	ZtWindow Window;
	Window.CreateWindow();
	glm::dvec2 ExpectedPosition{ 34.0, 2.4324 };
	ZtMouse::PositionCallback(Window.GetInternalWindow(), ExpectedPosition.x, ExpectedPosition.y);
	
	ZtEvent* Event = Window.GetEvent();
	ZtMouse* Mouse = Event->GetMouse();
	const std::vector<ZtMousePositionEvent>& Positions = Mouse->GetPositionEvents();
	ZtMousePositionEvent PositionEvent = Positions[0];
	glm::dvec2 ActualPosition = PositionEvent.Position;
	glm::bvec2 AreEqual = glm::equal(ExpectedPosition, ActualPosition);
	ASSERT_TRUE(glm::all(AreEqual));

	Mouse->SetMaxRememberedPositionEvents(2u);
	glm::dvec2 ExpectedSecondPosition{ 0.3432, 21.0 };
	ZtMouse::PositionCallback(Window.GetInternalWindow(), ExpectedSecondPosition.x, ExpectedSecondPosition.y);
	glm::dvec2 ActualSecondPosition = Positions[0].Position;
	AreEqual = glm::equal(ExpectedSecondPosition, ActualSecondPosition);
	ASSERT_TRUE(glm::all(AreEqual));
}

TEST_F(ZtMouseTests, GetPositionEventsTest)
{
	const std::vector<ZtMousePositionEvent>& Positions = Mouse.GetPositionEvents();
}

TEST_F(ZtMouseTests, SetMaxRememberedPositionEventsTest)
{
	size_t ExpectedMaxRememberedPositionEvents = 3u;
	Mouse.SetMaxRememberedPositionEvents(ExpectedMaxRememberedPositionEvents);
	size_t ActualMaxRememberedPositionEvents = Mouse.GetMaxRememberedPositionEvents();

	ASSERT_EQ(ActualMaxRememberedPositionEvents, ExpectedMaxRememberedPositionEvents);
}