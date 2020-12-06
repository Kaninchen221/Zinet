#pragma once

#include "gtest/gtest.h"

#include "Zinet/Frame/ZtWindow.h"

class ZtWindowTests : public ::testing::Test {
protected:

	class LoopTest : public zt::Loop {
	public:
		void start(const zt::LoopSettings settings) {}
	};

	using Window = zt::Window;
	using WindowSettings = zt::WindowSettings;
	using Loop = zt::Loop;
	using LoopSettings = zt::LoopSettings;

};

TEST_F(ZtWindowTests, constructorTest) {

	WindowSettings windowSettings;
	ASSERT_NO_THROW(Window::Window(windowSettings));

}

TEST_F(ZtWindowTests, setLoopTest) {

	WindowSettings windowSettings;
	Window window(windowSettings);

	std::unique_ptr<Loop> loop = std::make_unique<LoopMock>();
	window.setLoop(loop);

}

TEST_F(ZtWindowTests, startLoopThrowTest) {

	WindowSettings windowSettings;
	Window window(windowSettings);

	LoopSettings loopSettings;
	ASSERT_THROW(window.startLoop(loopSettings), zt::FrameException);

}