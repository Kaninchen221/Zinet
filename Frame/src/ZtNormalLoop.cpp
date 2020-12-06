#include "Zinet/Frame/ZtNormalLoop.h"

namespace zt {

	void NormalLoop::begin()
	{
		clock.start();
	
		timeForOneFrame = 1000000u / settings.maxFramesPerSecondCount;
	}
	
	void NormalLoop::loop(BaseWindow& baseWindow)
	{
	
		while (baseWindow.isOpen()) {
	
			auto elapsedTime = clock.getElapsedTime().microseconds();
		
			while (elapsedTime < timeForOneFrame) {

				event();
				update();
	
				elapsedTime += clock.getElapsedTime().microseconds();
			}
			
			render();
			clock.start();
		}
	
	}
	
	void NormalLoop::update()
	{
	}
	
	void NormalLoop::render()
	{
	}
	
	void NormalLoop::event()
	{
	}
	
	void NormalLoop::end()
	{
	}

}