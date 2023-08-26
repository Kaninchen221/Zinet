#pragma once

#include "Zinet/Window/ZtWindow.h"
#include "Zinet/Window/ZtVecTypes.h"
#include "Zinet/Window/ZtGLFW.h"

#include <gtest/gtest.h>

namespace zt::wd::tests
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

// 	TEST_F(WindowTests, GetRenderer)
// 	{
// 		typedef Renderer* (*ExpectedFunctionDeclaration)();
// 		using FunctionDeclaration = decltype(&Window::GetRenderer);
// 
// 		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
// 	}
// 
// 	TEST_F(WindowTests, SetRenderer)
// 	{
// 		typedef void(*ExpectedFunctionDeclaration)(Renderer&);
// 		using FunctionDeclaration = decltype(&Window::SetRenderer);
// 
// 		static_assert(std::is_same_v<ExpectedFunctionDeclaration, FunctionDeclaration>);
// 
// 		Renderer expectedRenderer;
// 		Window::SetRenderer(expectedRenderer);
// 		Renderer* actualRenderer = Window::GetRenderer();
// 
// 		ASSERT_EQ(&expectedRenderer, actualRenderer);
// 	}

	TEST_F(WindowTests, GetWindowSize)
	{
		typedef zt::Vector2ui(Window::* ExpectedFunctionDeclaration)() const;
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