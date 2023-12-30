#pragma once

#include "Zinet/Core/ZtCoreConfig.h"

#ifndef ZINET_STATIC

#ifdef ZINET_WINDOWS
#define ZINET_API_EXPORT __declspec(dllexport)
#define ZINET_API_IMPORT __declspec(dllimport)
#else 
#error Not supported OS platform
#endif // ZINET_WINDOWS

#ifdef ZINET_LIB
#define ZINET_MATH_LAYER_API ZINET_API_EXPORT
#else
#define ZINET_MATH_LAYER_API ZINET_API_IMPORT
#endif // ZINET_LIB


#else

#define ZINET_MATH_LAYER_API

#endif