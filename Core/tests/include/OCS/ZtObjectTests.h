#pragma once

#include "Zinet/Core/OCS/ZtObject.h"

#include "gtest/gtest.h"

class ZtObjectTests : public ::testing::Test
{
protected:

    ZtObject Object;

};

TEST_F(ZtObjectTests, BeginPlayTest)
{
    ZtBeginPlayReason BeginPlayReason = ZtBeginPlayReason::Loaded;
    Object.BeginPlay(BeginPlayReason);
}

TEST_F(ZtObjectTests, EndPlayTest)
{
    ZtEndPlayReason EndPlayReason = ZtEndPlayReason::Destroyed;
    Object.EndPlay(EndPlayReason);
}

TEST_F(ZtObjectTests, TickTest)
{
    float DeltaTime{};
    Object.Tick(DeltaTime);
}

TEST_F(ZtObjectTests, ShouldTickTest)
{
    bool bExpectedShouldTick = true;
    Object.SetShouldTick(bExpectedShouldTick);
    bool bActualShouldTick = Object.GetShouldTick();

    ASSERT_EQ(bActualShouldTick, bExpectedShouldTick);
}