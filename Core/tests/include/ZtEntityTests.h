#pragma once

#include "Zinet/Core/ZtEntity.h"

#include "gtest/gtest.h"

#include <memory>

class ZtEntityTests : public ::testing::Test
{
protected:

};

TEST_F(ZtEntityTests, UniqueIdentifierTest)
{
	ZtEntity FirstEntity;
	ZtEntity SecondEntity;

	size_t FirstUID = FirstEntity.GetUID();
	size_t SecondUID = SecondEntity.GetUID();

	ASSERT_GT(SecondUID, FirstUID);
}

