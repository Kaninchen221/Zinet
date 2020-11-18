#pragma once

#include "Zinet/Main/ZtClock.h"
#include "Zinet/Main/ZtTime.h"

#include "gtest/gtest.h"

class ZtClockTests : public ::testing::Test {
protected:

    ZtClockTests() {
        clock.start();
    }

    ~ZtClockTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    zt::Clock clock;
};

TEST_F(ZtClockTests, startTest) {
    
    zt::Time::Microseconds greaterThan = 1u;
    zt::Time::Microseconds lessThan = 1000u;

    auto time = clock.getElapsedTime();
    auto microseconds = time.microseconds();

    ASSERT_GT(microseconds, greaterThan);
    ASSERT_LT(microseconds, lessThan);
}

