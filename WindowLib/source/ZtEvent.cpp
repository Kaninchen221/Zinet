#include "Zinet/Window/ZtEvent.h"

namespace zt::wd
{
	const Window* Event::getWindow() const
	{
		return window;
	}

	void Event::bindCallbacks()
	{
		keyboard.bindCallbacks();
		mouse.bindCallbacks();
	}

}