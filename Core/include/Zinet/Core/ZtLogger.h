#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks-inl.h"

class ZtLogger
{

public:

	using SimpleConsoleLogger = std::shared_ptr<spdlog::logger>;

	inline static SimpleConsoleLogger CreateSimpleConsoleLogger(std::string Name);

};

ZtLogger::SimpleConsoleLogger ZtLogger::CreateSimpleConsoleLogger(std::string Name)
{
	SimpleConsoleLogger Logger = spdlog::stdout_color_mt(Name);
	return Logger;
}