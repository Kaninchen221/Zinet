#include "Zinet/Frame/ZtLoop.h"

#include "Zinet/Frame/ZtFrameException.h"

namespace zt {

	void Loop::start()
	{
		begin();

		loop();

		end();
	}

	void Loop::begin()
	{
		throw FrameException("begin must be covered by child class");
	}

	void Loop::loop()
	{
		throw FrameException("loop must be covered by child class");
	}

	void Loop::update()
	{
		throw FrameException("update must be covered by child class");
	}

	void Loop::render()
	{
		throw FrameException("render must be covered by child class");
	}

	void Loop::event()
	{
		throw FrameException("event must be covered by child class");
	}

	void Loop::end()
	{
		throw FrameException("end must be covered by child class");
	}

}