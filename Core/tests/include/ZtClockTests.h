#pragma once

#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

class ZtClockTests : public ::testing::Test 
{
protected:

    ZtClockTests() 
    {
    }

    ~ZtClockTests() override 
    {
    }

    void SetUp() override 
    {
    }

    void TearDown() override 
    {
    }

    ZtClock Clock;
};

TEST_F(ZtClockTests, StartTest) 
{
    
    ZtTime::NumericType GreaterThan = 0u;
    ZtTime::NumericType LessThan = 1000u;

    Clock.Start();
    ZtTime Time = Clock.GetElapsedTime();
    ZtTime::NumericType Microseconds = Time.GetAsMicroseconds();

    ASSERT_GT(Microseconds, GreaterThan);
    ASSERT_LT(Microseconds, LessThan);
}

TEST_F(ZtClockTests, RestartTest) 
{

    Clock.Start();

    ZtTime::NumericType GreaterThan = 0u;
    ZtTime::NumericType LessThan = 1000u;

    ZtTime Time = Clock.Restart();
    ZtTime::NumericType Microseconds = Time.GetAsMicroseconds();

    ASSERT_GT(Microseconds, GreaterThan);
    ASSERT_LT(Microseconds, LessThan);
}