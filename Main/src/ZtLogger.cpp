#include "Zinet/Main/ZtLogger.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <iostream>
#include <functional>

namespace zt {

    void Logger::Trace(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        auto function = std::bind([&]() { logger->trace(message); });

        CatchAndPrintExceptionToStandardOutput(function, __FUNCTION__);
    }

    void Logger::Debug(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        logger->debug(message);
    }

    void Logger::Info(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        auto function = std::bind([&]() { logger->info(message); });

        CatchAndPrintExceptionToStandardOutput(function, __FUNCTION__);
    }

    void Logger::Warn(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        logger->warn(message);
    }

    void Logger::Error(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        logger->error(message);
    }

    void Logger::Critical(const std::string& loggerName, const std::string& message)
    {
        auto logger = GetOrCreateLogger(loggerName);
        logger->critical(message);
    }

    std::string Logger::GetLoggsFolder()
    {
        return LoggsFolder;
    }

    std::string Logger::GetLoggsFileFormat()
    {
        return LoggsFileFormat;
    }

    Logger::LoggerT Logger::GetOrCreateLogger(const std::string& loggerName)
    {
        auto logger = GetLogger(loggerName);
        if (!logger) {
            auto logger = CreateDefaultLogger(loggerName);
        }

        logger = GetLogger(loggerName);
        return logger;
    }

    Logger::LoggerT Logger::CreateDefaultLogger(const std::string& loggerName)
    {
        auto logger = std::make_shared<spdlog::logger>(loggerName);

        AddStdoutSinkToLogger(logger);
        AddFileSinkToLogger(logger);

        spdlog::register_logger(logger);

        return logger;
    }

    Logger::LoggerT Logger::GetLogger(const std::string& loggerName)
    {
        return spdlog::get(loggerName);
    }

    void Logger::AddStdoutSinkToLogger(LoggerT logger)
    {
        auto& loggerSinks = logger->sinks();
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        loggerSinks.emplace_back(sink);
    }

    void Logger::AddFileSinkToLogger(LoggerT logger)
    {
        auto& loggerSinks = logger->sinks();
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
            LoggsFolder + logger->name() + LoggsFileFormat,
            Truncate
            );

        loggerSinks.emplace_back(sink);
    }

}