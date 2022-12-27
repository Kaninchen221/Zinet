#pragma once

#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTime.h"

#include <gtest/gtest.h>

namespace zt::tests
{

    class ClockTests : public ::testing::Test
    {
    protected:

        ClockTests()
        {
        }

        ~ClockTests() override
        {
        }

        void SetUp() override
        {
        }

        void TearDown() override
        {
        }

        Clock clock;
    };

    TEST_F(ClockTests, StartTest)
    {

        Time::NumericType greaterThan = 0u;
        Time::NumericType lessThan = 1000u;

        clock.start();
        Time time = clock.getElapsedTime();
        Time::NumericType microseconds = time.getAsMicroseconds();

        ASSERT_GT(microseconds, greaterThan);
        ASSERT_LT(microseconds, lessThan);
    }

    TEST_F(ClockTests, RestartTest)
    {

        clock.start();

        Time::NumericType greaterThan = 0u;
        Time::NumericType lessThan = 1000u;

        Time time = clock.restart();
        Time::NumericType microseconds = time.getAsMicroseconds();

        ASSERT_GT(microseconds, greaterThan);
        ASSERT_LT(microseconds, lessThan);
    }

}