#pragma once

#include <intrin.h>
#include <source_location>
#include <string>

namespace zt::core
{

#ifdef ZINET_DEBUG

	static inline bool Ensure(bool Value)
	{
		if (!Value)
		{
			__nop();
			__debugbreak();
		}

		return Value;
	}
#else
	static inline bool Ensure([[maybe_unused]] bool Value) { return true; }
#endif

	inline const std::string CurrentFunctionName()
	{
		std::source_location sourceLocation = std::source_location::current();
		return sourceLocation.function_name();
	}

}