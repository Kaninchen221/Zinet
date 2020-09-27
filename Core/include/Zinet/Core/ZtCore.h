#pragma once

#ifndef ZINET_STATIC

	#ifdef ZINET_WINDOWS /// MSVC
		
		#define ZINET_API_EXPORT __declspec(dllexport)
		#define ZINET_API_IMPORT __declspec(dllimport)

	#elif ZINET_LINUX /// GCC

		#define ZINET_API_EXPORT __attribute__ ((__visibility__ ("default")))
		#define ZINET_API_IMPORT __attribute__ ((__visibility__ ("default")))
	
	#else 

		#error Not supported OS platform

	#endif

#else

	#define ZINET_API_EXPORT
	#define ZINET_API_IMPORT

#endif