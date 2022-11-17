#pragma once

#pragma warning(disable:26812)
#pragma warning(disable:4820)

#ifndef ZINET_STATIC

	#ifdef ZINET_WINDOWS /// MSVC
		
		#define ZINET_API_EXPORT __declspec(dllexport)
		#define ZINET_API_IMPORT __declspec(dllimport)

	#else 

		#error Not supported OS platform

	#endif

#else

	#define ZINET_API_EXPORT
	#define ZINET_API_IMPORT

#endif

/// Temporary for future compability
#define ZINET_CORE_API

/// Turn On/Off Debug UI
#define ZINET_DEBUG_UI

#ifdef _DEBUG
	#define ZINET_DEBUG
#endif

// Define code breakpoint
// TODO Move it somewhere else
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
	static inline bool Ensure(bool Value) { return true; }
#endif

}