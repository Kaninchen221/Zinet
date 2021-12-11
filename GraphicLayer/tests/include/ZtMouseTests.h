#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtWindow.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"

#include "gtest/gtest.h"

#include "glm/vec2.hpp"
#include "glm/vector_relational.hpp"

namespace zt::gl::tests
{

	class ZtMouseTests : public ::testing::Test
	{
	protected:

		Mouse mouse;

	};

	TEST_F(ZtMouseTests, SetWindowTest)
	{
		Window ExpectedWindow;
		ExpectedWindow.CreateWindow();
		mouse.SetWindow(&ExpectedWindow);
		const Window* ActualWindow = mouse.GetWindow();

		ASSERT_EQ(&ExpectedWindow, ActualWindow);
	}

	TEST_F(ZtMouseTests, GetWindowTest)
	{
		const Window* ActualWindow = mouse.GetWindow();

		ASSERT_EQ(ActualWindow, nullptr);
	}

	TEST_F(ZtMouseTests, GetButtonsEventsTest)
	{
		const std::vector<MouseButtonEvent>& ButtonsEvents = mouse.GetButtonsEvents();
	}

	TEST_F(ZtMouseTests, SetMaxRememberedButtonsEventsTest)
	{
		size_t ExpectedMaxRememberedButtonsEvents = 4u;
		mouse.SetMaxRememberedButtonsEvents(ExpectedMaxRememberedButtonsEvents);
		size_t ActualMaxRememberedButtonsEvents = mouse.GetMaxRememberedButtonsEvents();

		ASSERT_EQ(ExpectedMaxRememberedButtonsEvents, ActualMaxRememberedButtonsEvents);

		ActualMaxRememberedButtonsEvents = mouse.GetButtonsEvents().size();

		ASSERT_EQ(ExpectedMaxRememberedButtonsEvents, ActualMaxRememberedButtonsEvents);
	}

	TEST_F(ZtMouseTests, ButtonCallbackTest)
	{
		Window Window;
		Window.CreateWindow();
		MouseButtonEvent ExpectedButtonEvent{};
		Mouse::ButtonCallback(Window.GetInternalWindow(), static_cast<int>(ExpectedButtonEvent.Button), static_cast<int>(ExpectedButtonEvent.Type), 0);
		const std::vector<MouseButtonEvent>& ButtonsEvents = mouse.GetButtonsEvents();
		size_t ActualButtonsEventsCount = ButtonsEvents.size();
		size_t ExpectedButtonsEventsCount = 1u;

		ASSERT_EQ(ActualButtonsEventsCount, ExpectedButtonsEventsCount);

		MouseButtonEvent ActualButtonEvent = ButtonsEvents[0];
		ASSERT_EQ(ExpectedButtonEvent, ActualButtonEvent);
	}

	TEST_F(ZtMouseTests, PositionCallbackTest)
	{
		Window Window;
		Window.CreateWindow();
		glm::dvec2 ExpectedPosition{ 34.0, 2.4324 };
		Mouse::PositionCallback(Window.GetInternalWindow(), ExpectedPosition.x, ExpectedPosition.y);

		Event* Event = Window.GetEvent();
		Mouse* Mouse = Event->GetMouse();
		const std::vector<MousePositionEvent>& Positions = Mouse->GetPositionEvents();
		MousePositionEvent PositionEvent = Positions[0];
		glm::dvec2 ActualPosition = PositionEvent.Position;
		glm::bvec2 AreEqual = glm::equal(ExpectedPosition, ActualPosition);
		ASSERT_TRUE(glm::all(AreEqual));

		Mouse->SetMaxRememberedPositionEvents(2u);
		glm::dvec2 ExpectedSecondPosition{ 0.3432, 21.0 };
		Mouse::PositionCallback(Window.GetInternalWindow(), ExpectedSecondPosition.x, ExpectedSecondPosition.y);
		glm::dvec2 ActualSecondPosition = Positions[0].Position;
		AreEqual = glm::equal(ExpectedSecondPosition, ActualSecondPosition);
		ASSERT_TRUE(glm::all(AreEqual));
	}

	TEST_F(ZtMouseTests, GetPositionEventsTest)
	{
		const std::vector<MousePositionEvent>& Positions = mouse.GetPositionEvents();
	}

	TEST_F(ZtMouseTests, SetMaxRememberedPositionEventsTest)
	{
		size_t ExpectedMaxRememberedPositionEvents = 3u;
		mouse.SetMaxRememberedPositionEvents(ExpectedMaxRememberedPositionEvents);
		size_t ActualMaxRememberedPositionEvents = mouse.GetMaxRememberedPositionEvents();

		ASSERT_EQ(ActualMaxRememberedPositionEvents, ExpectedMaxRememberedPositionEvents);
	}

}