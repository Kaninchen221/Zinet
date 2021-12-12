#pragma once

#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

namespace zt::tests
{

    class TimeTests : public ::testing::Test
    {
    protected:

        const Time::NumericType baseValue = 60000000000000.f;
        Time time;

        TimeTests()
            : time(baseValue)
        {
        }

        ~TimeTests() override {
        }

        void SetUp() override {
        }

        void TearDown() override {
        }

    };

    TEST_F(TimeTests, AssignTest)
    {
        Time::NumericType expectedValue = 69404.f;
        time = expectedValue;
    
        Time::NumericType nanoseconds = time.getAsNanoseconds();
    
        ASSERT_FLOAT_EQ(expectedValue, nanoseconds);
    }
    
    TEST_F(TimeTests, NanosecondsTest)
    {
        Time::NumericType nanoseconds = time.getAsNanoseconds();
        ASSERT_FLOAT_EQ(baseValue, nanoseconds);
    }
    
    TEST_F(TimeTests, MicrosecondsTest)
    {
        Time::NumericType expectedValue = baseValue / 1000.f;
        Time::NumericType microseconds = time.getAsMicroseconds();
        ASSERT_FLOAT_EQ(expectedValue, microseconds);
    }
    
    TEST_F(TimeTests, MillisecondsTest)
    {
        Time::NumericType expectedValue = baseValue / 1000.f / 1000.f;
        Time::NumericType milliseconds = time.getAsMilliseconds();
    
        ASSERT_FLOAT_EQ(expectedValue, milliseconds);
    }
    
    TEST_F(TimeTests, SecondsTest)
    {
        Time::NumericType expectedValue = baseValue / 1000.f / 1000.f / 1000.f;
        Time::NumericType seconds = time.getAsSeconds();
    
        ASSERT_FLOAT_EQ(expectedValue, seconds);
    }
    
    TEST_F(TimeTests, MinutesTest)
    {
        Time::NumericType expectedValue = baseValue / 1000.f / 1000.f / 1000.f / 60.f;
        Time::NumericType minutes = time.getAsMinutes();
    
        ASSERT_FLOAT_EQ(expectedValue, minutes);
    }
    
    TEST_F(TimeTests, HoursTest)
    {
        Time::NumericType expectedValue = baseValue / 1000.f / 1000.f / 1000.f / 60.f / 60.f;
        Time::NumericType hours = time.getAsHours();
    
        ASSERT_FLOAT_EQ(expectedValue, hours);
    }
    
    TEST_F(TimeTests, FromNanoseconds)
    {
        Time::NumericType expectedNanoseconds = 100.f;
        zt::Time actualTime = Time::FromNanoseconds(expectedNanoseconds);
        Time::NumericType actualNanoseconds = actualTime.getAsNanoseconds();
    
        ASSERT_FLOAT_EQ(expectedNanoseconds, actualNanoseconds);
    }
    
    TEST_F(TimeTests, FromMicroseconds)
    {
        Time::NumericType expectedMicroseconds = 100.f;
        zt::Time actualTime = Time::FromMicroseconds(expectedMicroseconds);
        Time::NumericType actualMicroseconds = actualTime.getAsMicroseconds();
    
        ASSERT_FLOAT_EQ(expectedMicroseconds, actualMicroseconds);
    }
    
    TEST_F(TimeTests, FromMilliseconds)
    {
        Time::NumericType expectedMilliseconds = 100.f;
        zt::Time actualTime = Time::FromMilliseconds(expectedMilliseconds);
        Time::NumericType actualMilliseconds = actualTime.getAsMilliseconds();
    
        ASSERT_FLOAT_EQ(expectedMilliseconds, actualMilliseconds);
    }
    
    TEST_F(TimeTests, FromSeconds)
    {
        Time::NumericType expectedSeconds = 100.f;
        zt::Time actualTime = Time::FromSeconds(expectedSeconds);
        Time::NumericType actualSeconds = actualTime.getAsSeconds();
    
        ASSERT_FLOAT_EQ(expectedSeconds, actualSeconds);
    }
    
    TEST_F(TimeTests, FromMinutes)
    {
        Time::NumericType expectedMinutes = 100.f;
        zt::Time actualTime = Time::FromMinutes(expectedMinutes);
        Time::NumericType actualMinutes = actualTime.getAsMinutes();
    
        ASSERT_FLOAT_EQ(expectedMinutes, actualMinutes);
    }
    
    TEST_F(TimeTests, FromHours)
    {
        Time::NumericType expectedHours = 100.f;
        zt::Time actualTime = Time::FromHours(expectedHours);
        Time::NumericType actualHours = actualTime.getAsHours();
    
        ASSERT_FLOAT_EQ(expectedHours, actualHours);
    }
}