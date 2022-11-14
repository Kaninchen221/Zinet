#pragma once

#include "Zinet/GraphicLayer/ZtMouse.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtMouseButtonEvent.h"
#include "Zinet/GraphicLayer/ZtMousePositionEvent.h"

#include <gtest/gtest.h>

#include "glm/vec2.hpp"
#include "glm/vector_relational.hpp"

namespace zt::gl::tests
{

	class ZtMouseTests : public ::testing::Test
	{
	protected:

		Mouse mouse;

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(ZtMouseTests, SetWindowTest)
	{
		Window expectedWindow;
		expectedWindow.create();
		mouse.setWindow(&expectedWindow);
		const Window* actualWindow = mouse.getWindow();

		ASSERT_EQ(&expectedWindow, actualWindow);
	}

	TEST_F(ZtMouseTests, GetWindowTest)
	{
		const Window* actualWindow = mouse.getWindow();

		ASSERT_EQ(actualWindow, nullptr);
	}

	TEST_F(ZtMouseTests, GetButtonsEventsTest)
	{
		const std::vector<MouseButtonEvent>& buttonsEvents = mouse.getButtonsEvents();
	}

	TEST_F(ZtMouseTests, SetMaxRememberedButtonsEventsTest)
	{
		size_t expectedMaxRememberedButtonsEvents = 4u;
		mouse.setMaxRememberedButtonsEvents(expectedMaxRememberedButtonsEvents);
		size_t actualMaxRememberedButtonsEvents = mouse.getMaxRememberedButtonsEvents();

		ASSERT_EQ(expectedMaxRememberedButtonsEvents, actualMaxRememberedButtonsEvents);

		actualMaxRememberedButtonsEvents = mouse.getButtonsEvents().size();

		ASSERT_EQ(expectedMaxRememberedButtonsEvents, actualMaxRememberedButtonsEvents);
	}

	TEST_F(ZtMouseTests, ButtonCallbackTest)
	{
		Window window;
		window.create();
		MouseButtonEvent expectedButtonEvent{};
		Mouse::ButtonCallback(window.getInternal(), static_cast<int>(expectedButtonEvent.button), static_cast<int>(expectedButtonEvent.type), 0);
		const std::vector<MouseButtonEvent>& buttonsEvents = mouse.getButtonsEvents();
		size_t actualButtonsEventsCount = buttonsEvents.size();
		size_t expectedButtonsEventsCount = 1u;

		ASSERT_EQ(actualButtonsEventsCount, expectedButtonsEventsCount);

		MouseButtonEvent actualButtonEvent = buttonsEvents[0];
		ASSERT_EQ(expectedButtonEvent, actualButtonEvent);
	}

	TEST_F(ZtMouseTests, PositionCallbackTest)
	{
		Window window;
		window.create();
		glm::dvec2 expectedPosition{ 34.0, 2.4324 };
		Mouse::PositionCallback(window.getInternal(), expectedPosition.x, expectedPosition.y);

		Event* event = window.getEvent();
		Mouse* mouse = event->getMouse();
		const std::vector<MousePositionEvent>& positions = mouse->getPositionEvents();
		MousePositionEvent positionEvent = positions[0];
		glm::dvec2 actualPosition = positionEvent.position;
		glm::bvec2 areEqual = glm::equal(expectedPosition, actualPosition);
		ASSERT_TRUE(glm::all(areEqual));

		mouse->setMaxRememberedPositionEvents(2u);
		glm::dvec2 expectedSecondPosition{ 0.3432, 21.0 };
		Mouse::PositionCallback(window.getInternal(), expectedSecondPosition.x, expectedSecondPosition.y);
		glm::dvec2 actualSecondPosition = positions[0].position;
		areEqual = glm::equal(expectedSecondPosition, actualSecondPosition);
		ASSERT_TRUE(glm::all(areEqual));
	}

	TEST_F(ZtMouseTests, GetPositionEventsTest)
	{
		const std::vector<MousePositionEvent>& positions = mouse.getPositionEvents();
	}

	TEST_F(ZtMouseTests, SetMaxRememberedPositionEventsTest)
	{
		size_t expectedMaxRememberedPositionEvents = 3u;
		mouse.setMaxRememberedPositionEvents(expectedMaxRememberedPositionEvents);
		size_t actualMaxRememberedPositionEvents = mouse.getMaxRememberedPositionEvents();

		ASSERT_EQ(actualMaxRememberedPositionEvents, expectedMaxRememberedPositionEvents);
	}

}