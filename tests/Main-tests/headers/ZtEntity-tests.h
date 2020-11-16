#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ECRS/ZtEntity.h"

class ZtEntityTests : public ::testing::Test {
protected:

};

TEST_F(ZtEntityTests, constructTest) {

	zt::Identificator id({});
	zt::Entity entity(id);

	static_assert(!std::is_default_constructible<zt::Entity>::value);

}

TEST_F(ZtEntityTests, getIdentificatorTest) {

	auto expectedIdNumber = 200u;
	zt::Identificator id(expectedIdNumber);
	zt::Entity entity(id);

	auto entityId = entity.getIdentificator();
	auto entityIdNumber = entityId.getNumber();

	ASSERT_EQ(expectedIdNumber, entityIdNumber);

}