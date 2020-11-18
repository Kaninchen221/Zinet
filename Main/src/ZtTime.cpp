#include "Zinet/Main/ZtTime.h"

namespace zt {

	constexpr Time::Time() noexcept
		: timeAsMicroseconds(0u)
	{
	}

	constexpr Time::Time(Microseconds microseconds) noexcept
		: timeAsMicroseconds(microseconds)
	{

	}

	constexpr Time& Time::operator=(Microseconds microseconds) noexcept
	{
		this->timeAsMicroseconds = microseconds;
		return *this;
	}

	constexpr Time::Microseconds Time::microseconds() const noexcept
	{
		return timeAsMicroseconds;
	}

	constexpr Time::Milliseconds Time::milliseconds() const noexcept
	{
		return timeAsMicroseconds / 1000u;
	}

	constexpr Time::Seconds Time::seconds() const noexcept
	{
		return milliseconds() / 1000u;
	}

	constexpr Time::Minutes Time::minutes() const noexcept
	{
		return seconds() / 60u;
	}

	constexpr Time::Hours Time::hours() const noexcept
	{
		return minutes() / 60u;
	}

}