#pragma once

#include <chrono>

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtTime.h"

namespace zt::core
{

	class ZINET_CORE_API Clock {

	public:

		using UnderlyingClock = std::chrono::system_clock;

		Clock() = default;
		Clock(const Clock& other) = default;
		Clock(Clock&& other) = default;

		Clock& operator = (const Clock& other) = default;
		Clock& operator = (Clock&& other) = default;

		~Clock() = default;

		void start();
		Time restart();
		Time getElapsedTime() const;

	private:

		UnderlyingClock::time_point savedTimePoint;
	};

}