#pragma once

#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLMouse.h"
#include "Zinet/GraphicLayer/ZtGLMouseButtonEvent.h"
#include "Zinet/GraphicLayer/ZtGLMousePositionEvent.h"

#include <gtest/gtest.h>

#include <glm/vec2.hpp>
#include <glm/vector_relational.hpp>

namespace zt::gl::tests
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
			GLFW::Deinit();
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