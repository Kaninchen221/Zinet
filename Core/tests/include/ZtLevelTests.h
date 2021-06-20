#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtLevel.h"
#include <type_traits>

class ZtLevelTests : public ::testing::Test 
{
protected:

	ZtLevel Level;

};

TEST_F(ZtLevelTests, TypeTest)
{
	static_assert(std::is_base_of_v<ZtObject, ZtLevel>, "ZtLevel must derive from ZtObject");
}