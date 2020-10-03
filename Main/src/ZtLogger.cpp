#include "Zinet/Main/ZtLogger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace zt {

    void Logger::Info(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->info(message);
    }

    Logger::LoggerT Logger::CreateLogger(const std::string& loggerName, const std::string& pattern)
    {
        auto logger = spdlog::stdout_color_mt(loggerName);
        logger->set_pattern(pattern);

        return logger;
    }

    Logger::LoggerT Logger::GetLogger(const std::string& loggerName)
    {
        return spdlog::get(loggerName);
    }

}