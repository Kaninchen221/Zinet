#include "Zinet/Core/ZtTime.h"

ZtTime::ZtTime()
	: TimeAsNanoseconds(0.f)
{

}

ZtTime::ZtTime(Nanoseconds Nanoseconds)
	: TimeAsNanoseconds(Nanoseconds)
{

}

ZtTime& ZtTime::operator=(Nanoseconds Nanoseconds)
{
	this->TimeAsNanoseconds = Nanoseconds;
	return *this;
}

ZtTime::Nanoseconds ZtTime::GetAsNanoseconds() const
{
	return TimeAsNanoseconds;
}

ZtTime::Microseconds ZtTime::GetAsMicroseconds() const
{
	return TimeAsNanoseconds / NanosecondsInMicrosecond;
}

ZtTime::Milliseconds ZtTime::GetAsMilliseconds() const
{
	return GetAsMicroseconds() / MicrosecondsInMillisecond;
}

ZtTime::Seconds ZtTime::GetAsSeconds() const
{
	return GetAsMilliseconds() / MillisecondsInSecond;
}

ZtTime::Minutes ZtTime::GetAsMinutes() const
{
	return GetAsSeconds() / SecondsInMinute;
}

ZtTime::Hours ZtTime::GetAsHours() const
{
	return GetAsMinutes() / MinutesInHour;
}