#pragma once

#include "Zinet/Core/ZtCoreConfig.h"

#ifndef ZINET_STATIC

#ifdef ZINET_WINDOWS
#define ZINET_API_EXPORT __declspec(dllexport)
#define ZINET_API_IMPORT __declspec(dllimport)
#else
	#error Not supported OS platform
	// We need this for project reflector
	#define ZINET_API_EXPORT
	#define ZINET_API_IMPORT
#endif // ZINET_WINDOWS

#ifdef ZINET_LIB
#define ZINET_ENGINE_API ZINET_API_EXPORT
#else
#define ZINET_ENGINE_API ZINET_API_IMPORT
#endif // ZINET_LIB


#else

#define ZINET_ENGINE_API

#endif

static_assert(false)
#define ZT_GENERATED_BODY(...)
#define ZT_REFLECT_NAMESPACE(...)
#define ZT_REFLECT_CLASS(...)
#define ZT_REFLECT_METHOD(...)
#define ZT_REFLECT_MEMBER(...)
#define ZT_REFLECT_STRUCT(...)