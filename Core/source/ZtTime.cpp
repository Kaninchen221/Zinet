#include "Zinet/Core/ZtTime.h"

ZtTime::ZtTime()
	: TimeAsNanoseconds(0.f)
{

}

ZtTime::ZtTime(NumericType Nanoseconds)
	: TimeAsNanoseconds(Nanoseconds)
{

}

ZtTime& ZtTime::operator=(NumericType Nanoseconds)
{
	this->TimeAsNanoseconds = Nanoseconds;
	return *this;
}

ZtTime::NumericType ZtTime::GetAsNanoseconds() const
{
	return TimeAsNanoseconds;
}

ZtTime::NumericType ZtTime::GetAsMicroseconds() const
{
	return TimeAsNanoseconds / NanosecondsInMicrosecond;
}

ZtTime::NumericType ZtTime::GetAsMilliseconds() const
{
	return GetAsMicroseconds() / MicrosecondsInMillisecond;
}

ZtTime::NumericType ZtTime::GetAsSeconds() const
{
	return GetAsMilliseconds() / MillisecondsInSecond;
}

ZtTime::NumericType ZtTime::GetAsMinutes() const
{
	return GetAsSeconds() / SecondsInMinute;
}

ZtTime::NumericType ZtTime::GetAsHours() const
{
	return GetAsMinutes() / MinutesInHour;
}

ZtTime ZtTime::FromNanoseconds(NumericType Nanoseconds)
{
	return ZtTime(Nanoseconds);
}

ZtTime ZtTime::FromMicroseconds(NumericType Microseconds)
{
	return FromNanoseconds(Microseconds * NanosecondsInMicrosecond);
}

ZtTime ZtTime::FromMilliseconds(NumericType Milliseconds)
{
	return FromMicroseconds(Milliseconds * MicrosecondsInMillisecond);
}

ZtTime ZtTime::FromSeconds(NumericType Seconds)
{
	return FromMilliseconds(Seconds * MillisecondsInSecond);
}

ZtTime ZtTime::FromMinutes(NumericType Minutes)
{
	return FromSeconds(Minutes * SecondsInMinute);
}

ZtTime ZtTime::FromHours(NumericType Hours)
{
	return FromMinutes(Hours * SecondsInMinute);
}
