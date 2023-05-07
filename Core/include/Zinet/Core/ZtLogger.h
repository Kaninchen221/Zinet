#pragma once

#include "Zinet/Core/ZtCore.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace zt
{
	class SimpleConsoleLogger;

	class ZINET_CORE_API Logger
	{
	public:

		// TODO: Error and Warning should fail tests

	};

	class ZINET_CORE_API ConsoleLogger : public std::shared_ptr<spdlog::logger>, public Logger
	{
	public:

		inline static ConsoleLogger Create(std::string name);


	};
}