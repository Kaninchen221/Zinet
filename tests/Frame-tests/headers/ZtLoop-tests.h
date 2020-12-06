#pragma once

#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtFrameException.h"

#include "gtest/gtest.h"

#include "mocks/ZtLoopMock.h"

#include <type_traits>

class ZtLoopTests : public ::testing::Test {
protected:

	using Loop = zt::Loop;

};

TEST_F(ZtLoopTests, startTest) {

	using ::testing::NaggyMock;

	NaggyMock<LoopMock> loopMock;
	zt::LoopSettings settings;

	EXPECT_CALL(loopMock, begin).Times(1);
	EXPECT_CALL(loopMock, loop).Times(1);
	EXPECT_CALL(loopMock, end).Times(1);

	loopMock.start(settings, Loop::BaseWindow());

}