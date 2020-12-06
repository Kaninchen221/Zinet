#pragma once

#include "Zinet/Frame/ZtLoop.h"

#include "Zinet/Main/ZtClock.h"
#include "Zinet/Main/ZtTime.h"

namespace zt {

	class NormalLoop : public Loop {

	public:

	private:

		void begin() override;
		
		void loop(BaseWindow& baseWindow) override;
		
		void update() override;
		
		void render() override;
		
		void event() override;
		
		void end() override;
		
		Clock clock;
		Time::Microseconds timeForOneFrame;
	};

}