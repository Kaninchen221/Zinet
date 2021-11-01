#include "Zinet/Core/ZtClock.h"
#include "Zinet/Core/ZtTime.h"

void ZtClock::Start()
{
	SavedTimePoint = UnderlyingClock::now();
}

ZtTime ZtClock::Restart()
{
	ZtTime ElapsedTime = GetElapsedTime();
	SavedTimePoint = UnderlyingClock::now();
	return ElapsedTime;
}

ZtTime ZtClock::GetElapsedTime() const
{
	using Duration = std::chrono::duration<UnderlyingClock::rep, UnderlyingClock::period>;

	thread_local UnderlyingClock::time_point ActualTimePoint;
	thread_local Duration Difference;
	thread_local ZtTime::NumericType Nanoseconds;
	thread_local ZtTime Time;

	ActualTimePoint = UnderlyingClock::now();
	Difference = ActualTimePoint - SavedTimePoint;
	Nanoseconds = static_cast<ZtFloat>(std::chrono::duration_cast<std::chrono::nanoseconds>(Difference).count());
	Time = Nanoseconds;
	return Time;
}