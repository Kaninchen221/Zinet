#pragma once

#include <gtest/gtest.h>
#include "Zinet/Core/ZtLogger.h"

namespace zt::tests
{

	class LoggerTests : public ::testing::Test
	{
	protected:

		Logger logger;

	};

	TEST_F(LoggerTests, CreateSimpleLoggerTest)
	{
		std::string name = "ZtLoggerTests";
		Logger::SimpleConsoleLogger SimpleConsoleLogger = Logger::CreateSimpleConsoleLogger(name);

		ASSERT_TRUE(SimpleConsoleLogger);
	}

}