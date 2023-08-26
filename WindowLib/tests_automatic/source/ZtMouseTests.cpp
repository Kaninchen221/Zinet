#pragma once

#include "Zinet/Window/ZtWindow.h"
#include "Zinet/Window/ZtMouse.h"
#include "Zinet/Window/ZtMouseButtonEvent.h"
#include "Zinet/Window/ZtMousePositionEvent.h"
#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

#include <glm/vec2.hpp>
#include <glm/vector_relational.hpp>

namespace zt::window::tests
{

	class MouseTests : public ::testing::Test
	{
	protected:

		Mouse mouse;

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			glfwTerminate();
		}
	};

	TEST_F(MouseTests, SetWindow)
	{
		Window expectedWindow;
		expectedWindow.create();
		mouse.setWindow(&expectedWindow);
		const Window* actualWindow = mouse.getWindow();

		ASSERT_EQ(&expectedWindow, actualWindow);
	}

	TEST_F(MouseTests, GetWindow)
	{
		const Window* actualWindow = mouse.getWindow();

		ASSERT_EQ(actualWindow, nullptr);
	}

	TEST_F(MouseTests, GetButtonsEvents)
	{
		[[maybe_unused]] const std::vector<MouseButtonEvent>& buttonsEvents = mouse.getButtonsEvents();
	}

	TEST_F(MouseTests, SetMaxRememberedButtonsEvents)
	{
		size_t expectedMaxRememberedButtonsEvents = 4u;
		mouse.setMaxRememberedButtonsEvents(expectedMaxRememberedButtonsEvents);
		size_t actualMaxRememberedButtonsEvents = mouse.getMaxRememberedButtonsEvents();

		ASSERT_EQ(expectedMaxRememberedButtonsEvents, actualMaxRememberedButtonsEvents);

		actualMaxRememberedButtonsEvents = mouse.getButtonsEvents().size();

		ASSERT_EQ(expectedMaxRememberedButtonsEvents, actualMaxRememberedButtonsEvents);
	}

	TEST_F(MouseTests, ButtonCallback)
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

	TEST(Mouse, PositionCallback)
	{
		GLFW::Init();

		Window window;
		window.create();
		zt::math::Vector2d expectedPosition{ 34.0, 2.0 };
		Mouse::PositionCallback(window.getInternal(), expectedPosition.x, expectedPosition.y);

		Event* event = window.getEvent();
		Mouse* mouse = event->getMouse();
		const std::vector<MousePositionEvent>& positions = mouse->getPositionEvents();
		MousePositionEvent positionEvent = positions[0];
		zt::math::Vector2d actualPosition = positionEvent.position;
		ASSERT_EQ(expectedPosition, actualPosition);

		mouse->setMaxRememberedPositionEvents(2u);
		zt::math::Vector2d expectedSecondPosition{ 67.0, 27.0 };
		Mouse::PositionCallback(window.getInternal(), expectedSecondPosition.x, expectedSecondPosition.y);
		zt::math::Vector2d actualSecondPosition = positions[0].position;
		ASSERT_EQ(expectedSecondPosition, actualSecondPosition);

		GLFW::Deinit();
	}

	TEST_F(MouseTests, GetPositionEvents)
	{
		[[maybe_unused]] const std::vector<MousePositionEvent>& positions = mouse.getPositionEvents();
	}

	TEST_F(MouseTests, SetMaxRememberedPositionEvents)
	{
		size_t expectedMaxRememberedPositionEvents = 3u;
		mouse.setMaxRememberedPositionEvents(expectedMaxRememberedPositionEvents);
		size_t actualMaxRememberedPositionEvents = mouse.getMaxRememberedPositionEvents();

		ASSERT_EQ(actualMaxRememberedPositionEvents, expectedMaxRememberedPositionEvents);
	}

}