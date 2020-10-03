#pragma once

#include "Zinet/Main/ZtMainConfig.h"

#include "spdlog/spdlog.h"

namespace zt {

	class ZINET_MAIN_API Logger {

	public:

		using LoggerT = std::shared_ptr<spdlog::logger>;

		//static void Trace(const std::string& loggerName, const std::string& message);
		//static void Debug(const std::string& loggerName, const std::string& message);
		static void Info(const std::string& loggerName, const std::string& message);
		//static void Warn(const std::string& loggerName, const std::string& message);
		//static void Error(const std::string& loggerName, const std::string& message);
		//static void Critical(const std::string& loggerName, const std::string& message);

		static LoggerT CreateLogger(const std::string& loggerName, const std::string& pattern);
		//static void CreateFileLogger(const std::string& loggerName, const std::string& pattern);

		static LoggerT GetLogger(const std::string& loggerName);

	private:

	};

}