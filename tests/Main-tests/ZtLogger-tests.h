#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtLogger.h"

class LoggerTest : public ::testing::Test {
protected:

    LoggerTest() {
    }

    ~LoggerTest() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(LoggerTest, ConstructTest) {
    
    zt::Logger logger;


}