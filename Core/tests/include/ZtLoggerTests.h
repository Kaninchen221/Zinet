#pragma once

#include "gtest/gtest.h"
#include "Zinet/Core/ZtLogger.h"

namespace zt::tests
{

	class LoggerTests : public ::testing::Test
	{
	protected:

		ZtLogger Logger;

	};

	TEST_F(LoggerTests, CreateSimpleLoggerTest)
	{
		std::string Name = "ZtLoggerTests";
		Logger::SimpleConsoleLogger SimpleConsoleLogger = Logger::CreateSimpleConsoleLogger(Name);

		ASSERT_TRUE(SimpleConsoleLogger);
	}

}