#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTime.h"

namespace zt
{

	void Clock::Start()
	{
		SavedTimePoint = UnderlyingClock::now();
	}

	Time Clock::Restart()
	{
		Time ElapsedTime = GetElapsedTime();
		SavedTimePoint = UnderlyingClock::now();
		return ElapsedTime;
	}

	Time Clock::GetElapsedTime() const
	{
		using Duration = std::chrono::duration<UnderlyingClock::rep, UnderlyingClock::period>;

		thread_local UnderlyingClock::time_point ActualTimePoint;
		thread_local Duration Difference;
		thread_local Time::NumericType Nanoseconds;
		thread_local Time Time;

		ActualTimePoint = UnderlyingClock::now();
		Difference = ActualTimePoint - SavedTimePoint;
		Nanoseconds = static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(Difference).count());
		Time = Nanoseconds;
		return Time;
	}

}