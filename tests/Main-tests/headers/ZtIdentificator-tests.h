#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtIdentificator.h"

#include <type_traits>

class ZtIdentificatorTests : public ::testing::Test {
protected:

};

TEST_F(ZtIdentificatorTests, parameterizedConstructorTest) {

	size_t expectedIdNumber = 200u;
	zt::Identificator id(expectedIdNumber);

	auto idNumber = id.getNumber();

	ASSERT_EQ(expectedIdNumber, idNumber);

}

TEST_F(ZtIdentificatorTests, cantBeDefaultConstructibleTest) {

	static_assert(!std::is_default_constructible<zt::Identificator>::value);
	
}

TEST_F(ZtIdentificatorTests, mustBeCopyableTest) {

	static_assert(std::is_copy_constructible<zt::Identificator>::value);
	static_assert(std::is_copy_assignable<zt::Identificator>::value);

}

TEST_F(ZtIdentificatorTests, mustBeMoveable) {

	static_assert(std::is_move_constructible<zt::Identificator>::value);
	static_assert(std::is_move_assignable<zt::Identificator>::value);

}