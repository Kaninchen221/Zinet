#pragma once

#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtFrameException.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <type_traits>

class ZtLoopTests : public ::testing::Test {
protected:

	using Loop = zt::Loop;

	struct LoopMock : public Loop {

		MOCK_METHOD(void, begin, (), (override));
		MOCK_METHOD(void, loop, (zt::Loop::BaseWindow& baseWindow), (override));
		MOCK_METHOD(void, update, (), (override));
		MOCK_METHOD(void, render, (), (override));
		MOCK_METHOD(void, event, (), (override));
		MOCK_METHOD(void, end, (), (override));

	};

};

TEST_F(ZtLoopTests, pass) {

	using ::testing::NaggyMock;

	NaggyMock<LoopMock> loopMock;
	zt::LoopSettings settings;

	EXPECT_CALL(loopMock, begin).Times(1);
	EXPECT_CALL(loopMock, loop).Times(1);
	EXPECT_CALL(loopMock, end).Times(1);

	loopMock.start(settings, Loop::BaseWindow());

}