#pragma once

#include <chrono>

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtTime.h"

class ZINET_CORE_API ZtClock {

public:

	using UnderlyingClock = std::chrono::system_clock;

	ZtClock() = default;
	ZtClock(const ZtClock& other) = default;
	ZtClock(ZtClock&& other) = default;

	ZtClock& operator = (const ZtClock& other) = default;
	ZtClock& operator = (ZtClock&& other) = default;

	~ZtClock() = default;

	void Start();
	ZtTime Restart();
	ZtTime GetElapsedTime() const;

private:

	UnderlyingClock::time_point SavedTimePoint;
};