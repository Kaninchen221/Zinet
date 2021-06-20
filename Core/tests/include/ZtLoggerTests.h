#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtLogger.h"

class ZtLoggerTests : public ::testing::Test 
{
protected:

	ZtLogger Logger;

};

TEST_F(ZtLoggerTests, CreateSimpleLoggerTest)
{
	std::string Name = "ZtLoggerTests";
	ZtLogger::SimpleConsoleLogger SimpleConsoleLogger = ZtLogger::CreateSimpleConsoleLogger(Name);

	ASSERT_TRUE(SimpleConsoleLogger);
}