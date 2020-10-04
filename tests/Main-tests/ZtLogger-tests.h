#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtLogger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

class LoggerTests : public ::testing::Test {
protected:

    LoggerTests() {
    }

    ~LoggerTests() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(LoggerTests, CreateAndGetLogger) {

    std::string loggerName = "CreateAndGetLogger logger";
    std::string pattern = "*** [%H:%M:%S %z] [thread %t] %v ***";

    zt::Logger::CreateLogger(loggerName, pattern);
    auto savedLogger = zt::Logger::GetLogger(loggerName);

    ASSERT_TRUE(savedLogger);
    ASSERT_EQ(savedLogger->name(), loggerName);

    zt::Logger::Info(loggerName, "Test Message");
}

TEST_F(LoggerTests, CreateAndGetFileLogger) {

    std::string loggerName = "CreateAndGetFileLogger logger";
    std::string pattern = "*** [%H:%M:%S %z] [thread %t] %v ***";

    zt::Logger::CreateFileLogger(loggerName, pattern);
    auto savedLogger = zt::Logger::GetLogger(loggerName);

    ASSERT_TRUE(savedLogger);
    ASSERT_EQ(savedLogger->name(), loggerName);

    zt::Logger::Info(loggerName, "Test Message");
}