#include "Zinet/Main/ZtClock.h"

#include "Zinet/Main/ZtTime.h"

namespace zt {

	void Clock::start()
	{
		savedTimePoint = UnderlyingClock::now();
	}

	Time Clock::getElapsedTime() const
	{
		using Duration = std::chrono::duration<UnderlyingClock::rep, UnderlyingClock::period>;

		thread_local UnderlyingClock::time_point actualTimePoint;
		thread_local Duration differenceAsNanoseconds;
		thread_local zt::Time::UnderlyingUnsignedInteger microseconds;
		thread_local zt::Time time;

		actualTimePoint = UnderlyingClock::now();
		differenceAsNanoseconds = actualTimePoint - savedTimePoint;
		microseconds = static_cast<zt::Time::UnderlyingUnsignedInteger>(differenceAsNanoseconds.count());
		time = microseconds;
		return time;
	}

}