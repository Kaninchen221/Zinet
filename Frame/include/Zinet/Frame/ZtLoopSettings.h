#pragma once

#include "Zinet/Frame/ZtFrameConfig.h"

#include <stdint.h>

namespace zt {

	struct ZINET_FRAME_API LoopSettings {

		uint32_t maxFramesPerSecondCount = 60u;


	};

}