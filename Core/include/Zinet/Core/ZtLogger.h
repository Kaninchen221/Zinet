#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace zt
{

	class Logger
	{

	public:

		using SimpleConsoleLogger = std::shared_ptr<spdlog::logger>;

		inline static SimpleConsoleLogger CreateSimpleConsoleLogger(std::string name);

	};

	inline Logger::SimpleConsoleLogger Logger::CreateSimpleConsoleLogger(std::string name)
	{
		SimpleConsoleLogger logger = spdlog::stdout_color_mt(name);
		return logger;
	}

}