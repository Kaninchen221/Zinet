#pragma once

#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

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

        Clock Clock;
    };

    TEST_F(ClockTests, StartTest)
    {

        Time::NumericType GreaterThan = 0u;
        Time::NumericType LessThan = 1000u;

        Clock.Start();
        Time Time = Clock.GetElapsedTime();
        Time::NumericType Microseconds = Time.GetAsMicroseconds();

        ASSERT_GT(Microseconds, GreaterThan);
        ASSERT_LT(Microseconds, LessThan);
    }

    TEST_F(ClockTests, RestartTest)
    {

        Clock.Start();

        Time::NumericType GreaterThan = 0u;
        Time::NumericType LessThan = 1000u;

        Time Time = Clock.Restart();
        Time::NumericType Microseconds = Time.GetAsMicroseconds();

        ASSERT_GT(Microseconds, GreaterThan);
        ASSERT_LT(Microseconds, LessThan);
    }

}