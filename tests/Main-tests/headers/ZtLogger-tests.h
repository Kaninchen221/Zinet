#pragma once

#include "gtest/gtest.h"

#include "Zinet/Main/ZtLogger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

#include <filesystem>
#include <fstream>

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

TEST_F(LoggerTests, LoggingTest) {

    std::string loggerName = "CreateAndGetLogger logger";
    std::string testMessage = "Test Message";

    zt::Logger::Info(loggerName, testMessage);
}