#include "Zinet/Frame/ZtLoop.h"

#include "Zinet/Frame/ZtFrameException.h"

namespace zt {

	void Loop::start(const zt::LoopSettings& settings, BaseWindow& baseWindow)
	{
		this->settings = settings;

		begin();

		loop(baseWindow);

		end();
	}

}