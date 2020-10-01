#include "Zinet/Main/ZtLogger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace zt {

	Logger::Logger() {
		initUnderlyingLogger();
	}

	void Logger::initUnderlyingLogger()
	{
		underlyingLogger = spdlog::stdout_color_mt("Main Logger");
	}

}
