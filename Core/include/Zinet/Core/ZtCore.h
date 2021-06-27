#pragma once

#pragma warning(disable:26812)

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

/// Breakpoint from code
#define ZT_BREAKPOINT __debugbreak

#define ZT_ALWAYS_BREAK ZT_BREAKPOINT

/// Macro utilities
#define CONCAT2(A, B) A ## B
#define CONCAT3(A, B, C) CONCAT2(A, B) ## C