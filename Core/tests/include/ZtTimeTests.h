#pragma once

#include "Zinet/Core/ZtTime.h"

#include "gtest/gtest.h"

class ZtTimeTests : public ::testing::Test {
protected:

    const ZtTime::Nanoseconds BaseValue = 60000000000000.f;
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

TEST_F(ZtTimeTests, AssignTest) {

    ZtTime::Microseconds ExpectedValue = 69404.f;
    Time = ExpectedValue;

    auto Nanoseconds = Time.GetAsNanoseconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Nanoseconds);
}

TEST_F(ZtTimeTests, NanosecondsTest) {

    auto Nanoseconds = Time.GetAsNanoseconds();
    ASSERT_FLOAT_EQ(BaseValue, Nanoseconds);
}

TEST_F(ZtTimeTests, MicrosecondsTest) {

    ZtTime::Microseconds ExpectedValue = BaseValue / 1000.f;
    auto Microseconds = Time.GetAsMicroseconds();
    ASSERT_FLOAT_EQ(ExpectedValue, Microseconds);
}

TEST_F(ZtTimeTests, MillisecondsTest) {

    ZtTime::Milliseconds ExpectedValue = BaseValue / 1000.f / 1000.f;
    auto Milliseconds = Time.GetAsMilliseconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Milliseconds);
}

TEST_F(ZtTimeTests, SecondsTest) {

    ZtTime::Milliseconds ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f;
    auto Seconds = Time.GetAsSeconds();

    ASSERT_FLOAT_EQ(ExpectedValue, Seconds);
}

TEST_F(ZtTimeTests, MinutesTest) {

    ZtTime::Minutes ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f;
    auto Minutes = Time.GetAsMinutes();

    ASSERT_FLOAT_EQ(ExpectedValue, Minutes);
}

TEST_F(ZtTimeTests, HoursTest) {

    ZtTime::Hours ExpectedValue = BaseValue / 1000.f / 1000.f / 1000.f / 60.f / 60.f;
    auto Hours = Time.GetAsHours();

    ASSERT_FLOAT_EQ(ExpectedValue, Hours);
}