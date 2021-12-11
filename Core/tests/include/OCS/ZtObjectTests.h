#pragma once

#include "Zinet/Core/OCS/ZtObject.h"

#include "gtest/gtest.h"

namespace zt::tests
{

    class ObjectTests : public ::testing::Test
    {
    protected:

        zt::Object Object;

    };

    TEST_F(ObjectTests, BeginPlayTest)
    {
        BeginPlayReason BeginPlayReason = BeginPlayReason::Loaded;
        Object.BeginPlay(BeginPlayReason);
    }

    TEST_F(ObjectTests, EndPlayTest)
    {
        EndPlayReason EndPlayReason = EndPlayReason::Destroyed;
        Object.EndPlay(EndPlayReason);
    }

    TEST_F(ObjectTests, TickTest)
    {
        float DeltaTime{};
        Object.Tick(DeltaTime);
    }

    TEST_F(ObjectTests, ShouldTickTest)
    {
        bool bExpectedShouldTick = true;
        Object.SetShouldTick(bExpectedShouldTick);
        bool bActualShouldTick = Object.GetShouldTick();

        ASSERT_EQ(bActualShouldTick, bExpectedShouldTick);
    }

}