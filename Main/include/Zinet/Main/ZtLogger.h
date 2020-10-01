#pragma once

#include "ZtMainConfig.h"

#include <memory>

namespace spdlog {
	class logger;
}

namespace zt {

	class ZINET_MAIN_API Logger {

	public:

		Logger();
		Logger(const Logger& other) = default;
		Logger(Logger&& other) = default;

		Logger& operator = (const Logger& other) = default;
		Logger& operator = (Logger&& other) = default;

		~Logger() noexcept = default;


	protected:

		void initUnderlyingLogger();

		std::shared_ptr<spdlog::logger> underlyingLogger;

	};

}