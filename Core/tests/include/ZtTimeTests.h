#pragma once

#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

namespace zt::tests
{

    class TimeTests : public ::testing::Test
    {
    protected:

        const Time::NumericType BaseValue = 60000000000000.f;
        Time Time;

        TimeTests()
            : Time(BaseValue)
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
        Time::NumericType ExpectedValue = 69404.f;
        Time = ExpectedValue;
    
        Time::NumericType Nanoseconds = Time.GetAsNanoseconds();
    
        ASSERT_FLOAT_EQ(ExpectedValue, Nanoseconds);
    }
    
    TEST_F(TimeTests, NanosecondsTest)
    {
        Time::NumericType Nanoseconds = Time.GetAsNanoseconds();
        ASSERT_FLOAT_EQ(BaseValue, Nanoseconds);
    }
    
    TEST_F(TimeTests, MicrosecondsTest)
    {
        Time::NumericType ExpectedValue = BaseValue / 1000.f;
        Time::NumericType Microseconds = Time.GetAsMicroseconds();
        ASSERT_FLOAT_EQ(ExpectedValue, Microseconds);
    }
    
    TEST_F(TimeTests, MillisecondsTest)
    {
        Time::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f;
        Time::NumericType Milliseconds = Time.GetAsMilliseconds();
    
        ASSERT_FLOAT_EQ(ExpectedValue, Milliseconds);
    }
    
    TEST_F(TimeTests, SecondsTest)
    {
        Time::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f;
        Time::NumericType Seconds = Time.GetAsSeconds();
    
        ASSERT_FLOAT_EQ(ExpectedValue, Seconds);
    }
    
    TEST_F(TimeTests, MinutesTest)
    {
        Time::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f;
        Time::NumericType Minutes = Time.GetAsMinutes();
    
        ASSERT_FLOAT_EQ(ExpectedValue, Minutes);
    }
    
    TEST_F(TimeTests, HoursTest)
    {
        Time::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f / 60.f;
        Time::NumericType Hours = Time.GetAsHours();
    
        ASSERT_FLOAT_EQ(ExpectedValue, Hours);
    }
    
    TEST_F(TimeTests, FromNanoseconds)
    {
        Time::NumericType ExpectedNanoseconds = 100.f;
        zt::Time ActualTime = Time::FromNanoseconds(ExpectedNanoseconds);
        Time::NumericType ActualNanoseconds = ActualTime.GetAsNanoseconds();
    
        ASSERT_FLOAT_EQ(ExpectedNanoseconds, ActualNanoseconds);
    }
    
    TEST_F(TimeTests, FromMicroseconds)
    {
        Time::NumericType ExpectedMicroseconds = 100.f;
        zt::Time ActualTime = Time::FromMicroseconds(ExpectedMicroseconds);
        Time::NumericType ActualMicroseconds = ActualTime.GetAsMicroseconds();
    
        ASSERT_FLOAT_EQ(ExpectedMicroseconds, ActualMicroseconds);
    }
    
    TEST_F(TimeTests, FromMilliseconds)
    {
        Time::NumericType ExpectedMilliseconds = 100.f;
        zt::Time ActualTime = Time::FromMilliseconds(ExpectedMilliseconds);
        Time::NumericType ActualMilliseconds = ActualTime.GetAsMilliseconds();
    
        ASSERT_FLOAT_EQ(ExpectedMilliseconds, ActualMilliseconds);
    }
    
    TEST_F(TimeTests, FromSeconds)
    {
        Time::NumericType ExpectedSeconds = 100.f;
        zt::Time ActualTime = Time::FromSeconds(ExpectedSeconds);
        Time::NumericType ActualSeconds = ActualTime.GetAsSeconds();
    
        ASSERT_FLOAT_EQ(ExpectedSeconds, ActualSeconds);
    }
    
    TEST_F(TimeTests, FromMinutes)
    {
        Time::NumericType ExpectedMinutes = 100.f;
        zt::Time ActualTime = Time::FromMinutes(ExpectedMinutes);
        Time::NumericType ActualMinutes = ActualTime.GetAsMinutes();
    
        ASSERT_FLOAT_EQ(ExpectedMinutes, ActualMinutes);
    }
    
    TEST_F(TimeTests, FromHours)
    {
        Time::NumericType ExpectedHours = 100.f;
        zt::Time ActualTime = Time::FromHours(ExpectedHours);
        Time::NumericType ActualHours = ActualTime.GetAsHours();
    
        ASSERT_FLOAT_EQ(ExpectedHours, ActualHours);
    }
}