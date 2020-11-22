#pragma once

#include "gtest/gtest.h"

#include "Zinet/Frame/ZtFrameException.h"

#include <type_traits>

class ZtFrameExceptionTests : public ::testing::Test {
protected:

	std::string exceptionMessage = "ex";

	void throwFrameException() {
		throw zt::FrameException(exceptionMessage);
	}

};

TEST_F(ZtFrameExceptionTests, mustBeCopyable) {

	ASSERT_TRUE(std::is_copy_constructible<zt::FrameException>::value);
	ASSERT_TRUE(std::is_copy_assignable<zt::FrameException>::value);

}

TEST_F(ZtFrameExceptionTests, catchAsFrameExceptionTest) {

	ASSERT_THROW(throwFrameException(), zt::FrameException);

}

TEST_F(ZtFrameExceptionTests, catchAsMainExceptionTest) {

	ASSERT_THROW(throwFrameException(), zt::MainException);

}

TEST_F(ZtFrameExceptionTests, catchAsStdExceptionTest) {

	ASSERT_THROW(throwFrameException(), std::exception);

}
