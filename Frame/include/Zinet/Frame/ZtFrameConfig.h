#pragma once

#include "Zinet/Core/ZtCore.h"

#ifdef ZINET_FRAME_EXPORT

	#define ZINET_FRAME_API ZINET_API_EXPORT

#else
	
	#define ZINET_FRAME_API ZINET_API_IMPORT

#endif