#pragma once

#include "Zinet/Frame/ZtLoop.h"
#include "Zinet/Frame/ZtFrameException.h"

#include "gtest/gtest.h"

#include <type_traits>

class ZtLoopTests : public ::testing::Test {
protected:

};

TEST_F(ZtLoopTests, constructibleTest) {

	ASSERT_TRUE(std::is_constructible<zt::Loop>::value);

}

TEST_F(ZtLoopTests, startMustThrowException) {

	zt::Loop loop;
	ASSERT_THROW(loop.start(), zt::FrameException);

}


