#pragma once

#include "ZtMainConfig.h"

#include <memory>
#include <string>

namespace spdlog {
	class logger;
}

namespace zt {

	class ZINET_MAIN_API LoggerBase {

	public:

		LoggerBase();
		LoggerBase(const LoggerBase& other) = default;
		LoggerBase(LoggerBase&& other) = default;

		LoggerBase& operator = (const LoggerBase& other) = default;
		LoggerBase& operator = (LoggerBase&& other) = default;

		virtual ~LoggerBase() noexcept = default;
		
		void trace(const std::string& message);
		void debug(const std::string& message);
		void info(const std::string& message);
		void warn(const std::string& message);
		void error(const std::string& message);
		void critical(const std::string& message);

	protected:

		virtual void initUnderlyingLogger() = 0;

		std::shared_ptr<spdlog::logger> underlyingLogger;

	};

}