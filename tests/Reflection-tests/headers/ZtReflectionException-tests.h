#pragma once

#include "gtest/gtest.h"

#include "Zinet/Reflection/ZtReflectionException.h"

#include <type_traits>

class ZtReflectionExceptionTests : public ::testing::Test {
protected:

	std::string exceptionMessage = "ex";

	void throwReflectionException() {
		throw zt::ReflectionException(exceptionMessage);
	}

};

TEST_F(ZtReflectionExceptionTests, mustBeCopyable) {

	ASSERT_TRUE(std::is_copy_constructible<zt::ReflectionException>::value);
	ASSERT_TRUE(std::is_copy_assignable<zt::ReflectionException>::value);

}

TEST_F(ZtReflectionExceptionTests, catchAsReflectionExceptionTest) {

	ASSERT_THROW(throwReflectionException(), zt::ReflectionException);

}

TEST_F(ZtReflectionExceptionTests, catchAsMainExceptionTest) {

	ASSERT_THROW(throwReflectionException(), zt::MainException);

}

TEST_F(ZtReflectionExceptionTests, catchAsStdExceptionTest) {

	ASSERT_THROW(throwReflectionException(), std::exception);

}
