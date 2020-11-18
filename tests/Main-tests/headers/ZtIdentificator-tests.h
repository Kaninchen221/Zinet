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

TEST_F(ZtIdentificatorTests, mustBeDefaultConstructibleTest) {

	static_assert(std::is_default_constructible<zt::Identificator>::value);
	
}

TEST_F(ZtIdentificatorTests, copyConstructorTest) {

	auto expectedNumber = 100u;

	zt::Identificator id(expectedNumber);
	zt::Identificator copy(id);
	auto copyNumber = copy.getNumber();

	ASSERT_EQ(expectedNumber, copyNumber);
}

TEST_F(ZtIdentificatorTests, copyAssignOperatorTest) {

	auto expectedNumber = 100u;

	zt::Identificator id(expectedNumber);
	zt::Identificator copy;
	copy = id;
	auto copyNumber = copy.getNumber();

	ASSERT_EQ(expectedNumber, copyNumber);
}

TEST_F(ZtIdentificatorTests, moveConstructorTest) {

	auto expectedNumber = 100u;

	zt::Identificator id(expectedNumber);
	zt::Identificator moved(std::move(id));
	auto movedNumber = moved.getNumber();

	ASSERT_EQ(expectedNumber, movedNumber);
}

TEST_F(ZtIdentificatorTests, moveAssignOperatorTest) {

	auto expectedNumber = 100u;

	zt::Identificator id(expectedNumber);
	zt::Identificator moved;
	moved = std::move(id);
	auto movedNumber = moved.getNumber();

	ASSERT_EQ(expectedNumber, movedNumber);
}

TEST_F(ZtIdentificatorTests, equalComparisonTest) {

	zt::Identificator id(6u);
	zt::Identificator equal(6u);

	ASSERT_EQ(id, equal);
}

TEST_F(ZtIdentificatorTests, notEqualComparisonTest) {

	zt::Identificator id(45u);
	zt::Identificator notEqual(4532534u);

	ASSERT_NE(id, notEqual);

}