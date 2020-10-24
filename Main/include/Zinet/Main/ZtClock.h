#pragma once

#include <chrono>

#include "Zinet/Main/ZtMainConfig.h"

namespace zt {

	class Time;

	class ZINET_MAIN_API Clock {

	public:

		using UnderlyingClock = std::chrono::system_clock;

		Clock() = default;
		Clock(const Clock& other) = default;
		Clock(Clock&& other) = default;

		Clock& operator = (const Clock& other) = default;
		Clock& operator = (Clock&& other) = default;

		~Clock() = default;

		void start();
		Time getElapsedTime() const;

	private:

		UnderlyingClock::time_point savedTimePoint;
	};

}