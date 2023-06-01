#pragma once

#include "Zinet/GraphicLayer/ZtGLWindow.h"
#include "Zinet/GraphicLayer/ZtGLGLFW.h"
#include "Zinet/GraphicLayer/ZtGLRenderer.h"
#include "Zinet/GraphicLayer/ZtGLVecTypes.h"

#include <gtest/gtest.h>

namespace zt::gl::tests
{

	class WindowTests : public ::testing::Test
	{
	protected:

		Window window{};

		void SetUp() override
		{
			GLFW::Init();
		}

		void TearDown() override
		{
			GLFW::Deinit();
		}
	};

	TEST_F(WindowTests, Create)
	{
		window.create();

		GLFWwindow* internalWindow = window.getInternal();
		ASSERT_TRUE(internalWindow);
	}

	TEST_F(WindowTests, BindFramebufferSizeCallbackTest)
	{
		window.create();

		GLFWwindow* glfwWindow = window.getInternal();
		GLFWframebuffersizefun actualPointer = glfwSetFramebufferSizeCallback(glfwWindow, nullptr);
		GLFWframebuffersizefun expectedPointer = &Window::FramebufferSizeCallback;

		ASSERT_EQ(actualPointer, expectedPointer);
	}

	TEST_F(WindowTests, IsOpenTest)
	{
		window.create();
	
		bool isOpen = window.isOpen();
		ASSERT_TRUE(isOpen);
	
		window.requestCloseWindow();
	
		isOpen = window.isOpen();
		ASSERT_FALSE(isOpen);
	}
	
	TEST_F(WindowTests, ShouldBeClosedTest)
	{
		window.create();
		GLboolean shouldBeClosed = window.shouldBeClosed();
	
		ASSERT_FALSE(shouldBeClosed);
	}
	
	TEST_F(WindowTests, GetEventTest)
	{
		[[maybe_unused]] Event* event = window.getEvent();
	}
	
	TEST_F(WindowTests, BindCallbacksTest)
	{
		window.create();
		window.bindCallbacks();
	}

	TEST_F(WindowTests, GetRenderer)
	{
		typedef Renderer* (Window::* ExpectedFunctionDeclaration)();
		using FunctionDeclaration = decltype(&Window::getRenderer);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	}

	TEST_F(WindowTests, SetRenderer)
	{
		// TODO (Low) Change it to static function
		typedef void(Window::* ExpectedFunctionDeclaration)(Renderer&);
		using FunctionDeclaration = decltype(&Window::setRenderer);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);

		Renderer expectedRenderer;
		window.setRenderer(expectedRenderer);
		Renderer* actualRenderer = window.getRenderer();

		ASSERT_EQ(&expectedRenderer, actualRenderer);
	}

	TEST_F(WindowTests, GetWindowSize)
	{
		typedef Vector2i(Window::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Window::getSize);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	}

	TEST_F(WindowTests, IsMinimized)
	{
		typedef bool(Window::* ExpectedFunctionDeclaration)() const;
		using FunctionDeclaration = decltype(&Window::isMinimized);

		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
	}
}