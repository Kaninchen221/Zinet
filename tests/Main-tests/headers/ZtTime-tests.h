#pragma once

#include "Zinet/Main/ZtTime.h"

#include "gtest/gtest.h"

class ZtTimeTests : public ::testing::Test {
protected:

    const zt::Time::Microseconds baseValue = 60000000000;
    zt::Time time;

    ZtTimeTests()
        : time(baseValue)
    {
    }

    ~ZtTimeTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(ZtTimeTests, assignTest) {

    zt::Time::Microseconds expectedValue = 69404u;
    time = expectedValue;

    auto microseconds = time.microseconds();

    ASSERT_EQ(expectedValue, microseconds);
}

TEST_F(ZtTimeTests, microsecondsTest) {

    auto microseconds = time.microseconds();
    ASSERT_EQ(baseValue, microseconds);
}

TEST_F(ZtTimeTests, millisecondsTest) {

    zt::Time::Milliseconds expectedValue = baseValue / 1000u;
    auto milliseconds = time.milliseconds();

    ASSERT_EQ(expectedValue, milliseconds);
}

TEST_F(ZtTimeTests, secondsTest) {

    zt::Time::Milliseconds expectedValue = baseValue / 1000u / 1000u;
    auto seconds = time.seconds();

    ASSERT_EQ(expectedValue, seconds);
}

TEST_F(ZtTimeTests, minutesTest) {

    zt::Time::Minutes expectedValue = baseValue / 1000u / 1000u / 60u;
    auto minutes = time.minutes();

    ASSERT_EQ(expectedValue, minutes);
}

TEST_F(ZtTimeTests, hoursTest) {

    zt::Time::Hours expectedValue = baseValue / 1000u / 1000u / 60u / 60u;
    auto hours = time.hours();

    ASSERT_EQ(expectedValue, hours);
}