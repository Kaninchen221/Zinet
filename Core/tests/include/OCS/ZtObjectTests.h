#pragma once

#include "Zinet/Core/OCS/ZtObject.h"

#include <gtest/gtest.h>

namespace zt::tests
{

    class ObjectTests : public ::testing::Test
    {
    protected:

        zt::Object object;

    };

    TEST_F(ObjectTests, BeginPlayTest)
    {
        BeginPlayReason beginPlayReason = BeginPlayReason::Loaded;
        object.beginPlay(beginPlayReason);
    }

    TEST_F(ObjectTests, EndPlayTest)
    {
        EndPlayReason endPlayReason = EndPlayReason::Destroyed;
        object.endPlay(endPlayReason);
    }

    TEST_F(ObjectTests, TickTest)
    {
        float deltaTime{};
        object.tick(deltaTime);
    }

    TEST_F(ObjectTests, ShouldTickTest)
    {
        bool expectedShouldTick = true;
        object.setShouldTick(expectedShouldTick);
        bool actualShouldTick = object.getShouldTick();

        ASSERT_EQ(actualShouldTick, expectedShouldTick);
    }

}