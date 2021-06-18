#pragma once

#include "ZtCore.h"

class ZINET_CORE_API ZtTime {

public:

	using NumericType = float;
	using Nanoseconds = NumericType;
	using Microseconds = NumericType;
	using Milliseconds = NumericType;
	using Seconds = NumericType;
	using Minutes = NumericType;
	using Hours = NumericType;

	inline static const NumericType NanosecondsInMicrosecond = 1000.f;
	inline static const NumericType MicrosecondsInMillisecond = 1000.f;
	inline static const NumericType MillisecondsInSecond = 1000.f;
	inline static const NumericType MicrosecondsInSecond = MicrosecondsInMillisecond * MillisecondsInSecond;
	inline static const NumericType SecondsInMinute = 60.f;
	inline static const NumericType MinutesInHour = 60.f;

	ZtTime();
	ZtTime(const ZtTime& other) = default;
	ZtTime(ZtTime&& other) = default;
	ZtTime(Nanoseconds Nanoseconds);

	ZtTime& operator = (const ZtTime& Other) = default;
	ZtTime& operator = (ZtTime&& Other) = default;
	ZtTime& operator = (Nanoseconds Nanoseconds);

	~ZtTime() noexcept = default;

	Nanoseconds GetAsNanoseconds() const;
	Microseconds GetAsMicroseconds() const;
	Milliseconds GetAsMilliseconds() const;
	Seconds GetAsSeconds() const;
	Minutes GetAsMinutes() const;
	Hours GetAsHours() const;

private:

	Microseconds TimeAsNanoseconds = 0.f;
};