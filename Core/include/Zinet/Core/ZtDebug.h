#pragma once

#include <intrin.h>
namespace zt
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

}