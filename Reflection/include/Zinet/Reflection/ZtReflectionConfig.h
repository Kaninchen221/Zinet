#pragma once

#include "Zinet/Core/ZtCore.h"

#ifdef ZINET_REFLECTION_EXPORT

	#define ZINET_REFLECTION_API ZINET_API_EXPORT

#else
	
	#define ZINET_REFLECTION_API ZINET_API_IMPORT

#endif