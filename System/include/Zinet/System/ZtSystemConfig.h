#pragma once

#include "Zinet/Core/ZtCore.h"

#ifdef ZINET_SYSTEM_EXPORT

	#define ZINET_SYSTEM_API ZINET_API_EXPORT

#else
	
	#define ZINET_SYSTEM_API ZINET_API_IMPORT

#endif