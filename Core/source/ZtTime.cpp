#include "Zinet/Core/ZtTime.h"

namespace zt
{

	Time::Time()
		: TimeAsNanoseconds(0.f)
	{

	}

	Time::Time(NumericType Nanoseconds)
		: TimeAsNanoseconds(Nanoseconds)
	{

	}

	Time& Time::operator=(NumericType Nanoseconds)
	{
		this->TimeAsNanoseconds = Nanoseconds;
		return *this;
	}

	Time::NumericType Time::GetAsNanoseconds() const
	{
		return TimeAsNanoseconds;
	}

	Time::NumericType Time::GetAsMicroseconds() const
	{
		return TimeAsNanoseconds / NanosecondsInMicrosecond;
	}

	Time::NumericType Time::GetAsMilliseconds() const
	{
		return GetAsMicroseconds() / MicrosecondsInMillisecond;
	}

	Time::NumericType Time::GetAsSeconds() const
	{
		return GetAsMilliseconds() / MillisecondsInSecond;
	}

	Time::NumericType Time::GetAsMinutes() const
	{
		return GetAsSeconds() / SecondsInMinute;
	}

	Time::NumericType Time::GetAsHours() const
	{
		return GetAsMinutes() / MinutesInHour;
	}

	Time Time::FromNanoseconds(NumericType Nanoseconds)
	{
		return Time(Nanoseconds);
	}

	Time Time::FromMicroseconds(NumericType Microseconds)
	{
		return FromNanoseconds(Microseconds * NanosecondsInMicrosecond);
	}

	Time Time::FromMilliseconds(NumericType Milliseconds)
	{
		return FromMicroseconds(Milliseconds * MicrosecondsInMillisecond);
	}

	Time Time::FromSeconds(NumericType Seconds)
	{
		return FromMilliseconds(Seconds * MillisecondsInSecond);
	}

	Time Time::FromMinutes(NumericType Minutes)
	{
		return FromSeconds(Minutes * SecondsInMinute);
	}

	Time Time::FromHours(NumericType Hours)
	{
		return FromMinutes(Hours * SecondsInMinute);
	}

}