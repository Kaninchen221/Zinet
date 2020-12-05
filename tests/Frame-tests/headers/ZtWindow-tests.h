#pragma once

#include "gtest/gtest.h"

#include "Zinet/Frame/ZtWindow.h"

class ZtWindowTests : public ::testing::Test {
protected:

	class LoopTest : public zt::Loop {
	public:
		void start(const zt::LoopSettings settings) {}
	};

	using Window = zt::Window<LoopTest>;

};

TEST_F(ZtWindowTests, constructorTest) {

	zt::WindowSettings windowSettings;
	Window window(windowSettings);
	
}