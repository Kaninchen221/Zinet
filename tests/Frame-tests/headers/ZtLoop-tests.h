#pragma once

#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtFrameException.h"

#include "gtest/gtest.h"

#include <type_traits>

class ZtLoopTests : public ::testing::Test {
protected:

	using Loop = zt::Loop;

};

TEST_F(ZtLoopTests, constructibleTest) {

	ASSERT_TRUE(std::is_constructible<Loop>::value);

}

TEST_F(ZtLoopTests, startMustThrowException) {

	Loop loop;
	zt::LoopSettings settings;
	ASSERT_THROW(loop.start(settings, Loop::BaseWindow()), zt::FrameException);

}


