#include "Zinet/Core/ZtLogger.h"

namespace zt
{
	zt::ConsoleLogger ConsoleLogger::Create(std::string name)
	{
		ConsoleLogger logger{ spdlog::stdout_color_mt(name) };
		return logger;
	}
}