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
		Time(NumericType Nanoseconds);

		Time& operator = (const Time& Other) = default;
		Time& operator = (Time&& Other) = default;
		Time& operator = (NumericType Nanoseconds);

		~Time() noexcept = default;

		NumericType GetAsNanoseconds() const;
		NumericType GetAsMicroseconds() const;
		NumericType GetAsMilliseconds() const;
		NumericType GetAsSeconds() const;
		NumericType GetAsMinutes() const;
		NumericType GetAsHours() const;

		static Time FromNanoseconds(NumericType Nanoseconds);
		static Time FromMicroseconds(NumericType Microseconds);
		static Time FromMilliseconds(NumericType Milliseconds);
		static Time FromSeconds(NumericType Seconds);
		static Time FromMinutes(NumericType Minutes);
		static Time FromHours(NumericType Hours);

	private:

		NumericType TimeAsNanoseconds = 0.f;
	};

}