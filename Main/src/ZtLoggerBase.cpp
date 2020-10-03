#include "Zinet/Main/ZtLoggerBase.h"

#include "Zinet/Main/ZtMainException.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <iostream>

namespace zt {

	LoggerBase::LoggerBase() {
		try {
			initUnderlyingLogger();
		}
		catch (const spdlog::spdlog_ex& spdlog_ex) {
			throw MainException(std::string("LoggerBase::LoggerBase throw spdlog exception : ") + spdlog_ex.what());
		}
	}

	void LoggerBase::trace(const std::string& message)
	{
		underlyingLogger->trace(message);
	}

	void LoggerBase::debug(const std::string& message)
	{
		underlyingLogger->debug(message);
	}

	void LoggerBase::info(const std::string& message)
	{
		underlyingLogger->info(message);
	}

	void LoggerBase::warn(const std::string& message)
	{
		underlyingLogger->warn(message);
	}

	void LoggerBase::error(const std::string& message)
	{
		underlyingLogger->error(message);
	}

	void LoggerBase::critical(const std::string& message)
	{
		underlyingLogger->critical(message);
	}

}
