#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtWorld.h"
#include <type_traits>

class ZtWorldTests : public ::testing::Test 
{
protected:

	ZtWorld World;

};

TEST_F(ZtWorldTests, TypeTest)
{

}

TEST_F(ZtWorldTests, GetLevelTest)
{
	ZtLevel Level = World.GetLevel();
}