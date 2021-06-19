#pragma once

#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

class ZtTimeTests : public ::testing::Test {
protected:

    const ZtTime::NumericType BaseValue = 60000000000000.f;
    ZtTime Time;

    ZtTimeTests()
        : Time(BaseValue)
    {
    }

    ~ZtTimeTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(ZtTimeTests, AssignTest) 
{
    ZtTime::NumericType ExpectedValue = 69404.f;
    Time = ExpectedValue;

    ZtTime::NumericType Nanoseconds = Time.GetAsNanoseconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Nanoseconds);
}

TEST_F(ZtTimeTests, NanosecondsTest) 
{
    ZtTime::NumericType Nanoseconds = Time.GetAsNanoseconds();
    ASSERT_FLOAT_EQ(BaseValue, Nanoseconds);
}

TEST_F(ZtTimeTests, MicrosecondsTest) 
{
    ZtTime::NumericType ExpectedValue = BaseValue / 1000.f;
    ZtTime::NumericType Microseconds = Time.GetAsMicroseconds();
    ASSERT_FLOAT_EQ(ExpectedValue, Microseconds);
}

TEST_F(ZtTimeTests, MillisecondsTest) 
{
    ZtTime::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f;
    ZtTime::NumericType Milliseconds = Time.GetAsMilliseconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Milliseconds);
}

TEST_F(ZtTimeTests, SecondsTest) 
{
    ZtTime::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f;
    ZtTime::NumericType Seconds = Time.GetAsSeconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Seconds);
}

TEST_F(ZtTimeTests, MinutesTest) 
{
    ZtTime::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f;
    ZtTime::NumericType Minutes = Time.GetAsMinutes();

    ASSERT_FLOAT_EQ(ExpectedValue, Minutes);
}

TEST_F(ZtTimeTests, HoursTest) 
{
    ZtTime::NumericType ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f / 60.f;
    ZtTime::NumericType Hours = Time.GetAsHours();

    ASSERT_FLOAT_EQ(ExpectedValue, Hours);
}

TEST_F(ZtTimeTests, FromNanoseconds)
{
    ZtTime::NumericType ExpectedNanoseconds = 100.f;
    ZtTime ActualTime = ZtTime::FromNanoseconds(ExpectedNanoseconds);
    ZtTime::NumericType ActualNanoseconds = ActualTime.GetAsNanoseconds();

    ASSERT_FLOAT_EQ(ExpectedNanoseconds, ActualNanoseconds);
}

TEST_F(ZtTimeTests, FromMicroseconds)
{
    ZtTime::NumericType ExpectedMicroseconds = 100.f;
    ZtTime ActualTime = ZtTime::FromMicroseconds(ExpectedMicroseconds);
    ZtTime::NumericType ActualMicroseconds = ActualTime.GetAsMicroseconds();

    ASSERT_FLOAT_EQ(ExpectedMicroseconds, ActualMicroseconds);
}

TEST_F(ZtTimeTests, FromMilliseconds)
{
    ZtTime::NumericType ExpectedMilliseconds = 100.f;
    ZtTime ActualTime = ZtTime::FromMilliseconds(ExpectedMilliseconds);
    ZtTime::NumericType ActualMilliseconds = ActualTime.GetAsMilliseconds();

    ASSERT_FLOAT_EQ(ExpectedMilliseconds, ActualMilliseconds);
}

TEST_F(ZtTimeTests, FromSeconds)
{
    ZtTime::NumericType ExpectedSeconds = 100.f;
    ZtTime ActualTime = ZtTime::FromSeconds(ExpectedSeconds);
    ZtTime::NumericType ActualSeconds = ActualTime.GetAsSeconds();

    ASSERT_FLOAT_EQ(ExpectedSeconds, ActualSeconds);
}

TEST_F(ZtTimeTests, FromMinutes)
{
    ZtTime::NumericType ExpectedMinutes = 100.f;
    ZtTime ActualTime = ZtTime::FromMinutes(ExpectedMinutes);
    ZtTime::NumericType ActualMinutes = ActualTime.GetAsMinutes();

    ASSERT_FLOAT_EQ(ExpectedMinutes, ActualMinutes);
}

TEST_F(ZtTimeTests, FromHours)
{
    ZtTime::NumericType ExpectedHours = 100.f;
    ZtTime ActualTime = ZtTime::FromHours(ExpectedHours);
    ZtTime::NumericType ActualHours = ActualTime.GetAsHours();

    ASSERT_FLOAT_EQ(ExpectedHours, ActualHours);
}