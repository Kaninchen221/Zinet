#pragma once

#include <gtest/gtest.h>
#include "Zinet/Core/ZtLogger.h"

namespace zt::tests
{

	class LoggerTests : public ::testing::Test
	{
	protected:

		Logger logger;

		static_assert(std::is_base_of_v<std::shared_ptr<spdlog::logger>, ConsoleLogger>);
		static_assert(std::is_base_of_v<Logger, ConsoleLogger>);
	};

	TEST_F(LoggerTests, CreateConsoleLoggerTest)
	{
		std::string name = "ZtLoggerTests";
		ConsoleLogger consoleLogger = ConsoleLogger::Create(name);

		ASSERT_TRUE(consoleLogger);
	}

}