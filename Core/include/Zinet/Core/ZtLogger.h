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

	class ZINET_CORE_API ConsoleLogger : public Logger
	{
	public:

		inline static ConsoleLogger Create(std::string name);

		spdlog::logger* operator -> () { return internal.get(); }
		const spdlog::logger* operator -> () const { return internal.get(); }

		spdlog::logger* operator ()() { return internal.get(); }
		const spdlog::logger* operator ()() const { return internal.get(); }

		operator bool() { return internal.operator bool(); }
		operator bool() const { return internal.operator bool(); }

		void turnOff();
		void turnOn();

	protected:

		std::shared_ptr<spdlog::logger> internal;
		spdlog::level::level_enum lastLevel;

	};

	ConsoleLogger ConsoleLogger::Create(std::string name)
	{
		ConsoleLogger logger;
		logger.internal = spdlog::stdout_color_mt(name);
		return logger;

	}
}