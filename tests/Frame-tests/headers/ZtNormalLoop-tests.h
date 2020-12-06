#pragma once

#include "gtest/gtest.h"

#include "Zinet/Frame/ZtNormalLoop.h"

class ZtNormalLoopTests : public ::testing::Test {
protected:

	using NormalLoop = zt::NormalLoop;
	using Settings = zt::LoopSettings;
	using BaseWindow = zt::Loop::BaseWindow;
};

TEST_F(ZtNormalLoopTests, startTest) {

	BaseWindow window;
	NormalLoop normalLoop;
	Settings settings;

	window.create(sf::VideoMode(200, 200), "title");
	//normalLoop.start(settings, window);

}