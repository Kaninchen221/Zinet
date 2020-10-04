#include "Zinet/Main/ZtLogger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace zt {

    void Logger::Trace(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->trace(message);
    }

    void Logger::Debug(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->debug(message);
    }

    void Logger::Info(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->info(message);
    }

    void Logger::Warn(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->warn(message);
    }

    void Logger::Error(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->error(message);
    }

    void Logger::Critical(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetLogger(loggerName);
        logger->critical(message);
    }

    Logger::LoggerT Logger::CreateLogger(const std::string& loggerName, const std::string& pattern)
    {
        auto logger = spdlog::stdout_color_mt(loggerName);
        logger->set_pattern(pattern);

        return logger;
    }

    Logger::LoggerT Logger::CreateFileLogger(const std::string& loggerName, const std::string& pattern)
    {
        auto logger = spdlog::basic_logger_mt(loggerName, "logs/" + loggerName + ".txt");
        logger->set_pattern(pattern);

        return logger;
    }

    Logger::LoggerT Logger::GetLogger(const std::string& loggerName)
    {
        return spdlog::get(loggerName);
    }

}