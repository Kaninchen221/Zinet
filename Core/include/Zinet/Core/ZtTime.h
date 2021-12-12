#pragma once

#include "ZtCore.h"

namespace zt
{

	class ZINET_CORE_API Time {

	public:

		using NumericType = float;

		inline static const NumericType NanosecondsInMicrosecond = 1000.f;
		inline static const NumericType MicrosecondsInMillisecond = 1000.f;
		inline static const NumericType MillisecondsInSecond = 1000.f;
		inline static const NumericType MicrosecondsInSecond = MicrosecondsInMillisecond * MillisecondsInSecond;
		inline static const NumericType SecondsInMinute = 60.f;
		inline static const NumericType MinutesInHour = 60.f;

		Time();
		Time(const Time& other) = default;
		Time(Time&& other) = default;
		Time(NumericType nanoseconds);

		Time& operator = (const Time& other) = default;
		Time& operator = (Time&& other) = default;
		Time& operator = (NumericType nanoseconds);

		~Time() noexcept = default;

		NumericType getAsNanoseconds() const;
		NumericType getAsMicroseconds() const;
		NumericType getAsMilliseconds() const;
		NumericType getAsSeconds() const;
		NumericType getAsMinutes() const;
		NumericType getAsHours() const;

		static Time FromNanoseconds(NumericType nanoseconds);
		static Time FromMicroseconds(NumericType microseconds);
		static Time FromMilliseconds(NumericType milliseconds);
		static Time FromSeconds(NumericType seconds);
		static Time FromMinutes(NumericType minutes);
		static Time FromHours(NumericType hours);

	private:

		NumericType timeAsNanoseconds = 0.f;
	};

}