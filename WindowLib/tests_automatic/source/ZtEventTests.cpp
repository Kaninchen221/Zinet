#pragma once

#include "Zinet/Window/ZtEvent.h"
#include "Zinet/Window/ZtWindow.h"

#include <GLFW/glfw3.h>

#include <gtest/gtest.h>

namespace zt::window::tests
{

	class EventTests : public ::testing::Test
	{
	protected:

		Event event{};

	};

	TEST_F(EventTests, SetWindow)
	{
		glfwInit();

		Window expectedWindow;
		expectedWindow.create();
		event.setWindow(&expectedWindow);
		const Window* actualWindow = event.getWindow();

		ASSERT_EQ(&expectedWindow, actualWindow);

		glfwTerminate();
	}

	TEST_F(EventTests, GetWindow)
	{
		const Window* window = event.getWindow();

		ASSERT_EQ(window, nullptr);
	}

	TEST_F(EventTests, PollEvents)
	{
		event.pollEvents();
	}

	TEST_F(EventTests, GetKeyboard)
	{
		Keyboard* keyboard = event.getKeyboard();

		ASSERT_NE(keyboard, nullptr);
	}

	TEST_F(EventTests, GetMouse)
	{
		Mouse* mouse = event.getMouse();

		ASSERT_NE(mouse, nullptr);
	}

}