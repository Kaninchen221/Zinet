#pragma once

#include "Zinet/Core/ZtCore.h"

#ifdef ZINET_MAIN_EXPORT

	#define ZINET_MAIN_API ZINET_API_EXPORT

#else
	
	#define ZINET_MAIN_API ZINET_API_IMPORT

#endif