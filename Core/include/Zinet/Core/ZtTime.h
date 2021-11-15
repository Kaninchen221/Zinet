#pragma once

#include "ZtCore.h"

class ZINET_CORE_API ZtTime {

public:

	using NumericType = float;

	inline static const NumericType NanosecondsInMicrosecond = 1000.f;
	inline static const NumericType MicrosecondsInMillisecond = 1000.f;
	inline static const NumericType MillisecondsInSecond = 1000.f;
	inline static const NumericType MicrosecondsInSecond = MicrosecondsInMillisecond * MillisecondsInSecond;
	inline static const NumericType SecondsInMinute = 60.f;
	inline static const NumericType MinutesInHour = 60.f;

	ZtTime();
	ZtTime(const ZtTime& other) = default;
	ZtTime(ZtTime&& other) = default;
	ZtTime(NumericType Nanoseconds);

	ZtTime& operator = (const ZtTime& Other) = default;
	ZtTime& operator = (ZtTime&& Other) = default;
	ZtTime& operator = (NumericType Nanoseconds);

	~ZtTime() noexcept = default;

	NumericType GetAsNanoseconds() const;
	NumericType GetAsMicroseconds() const;
	NumericType GetAsMilliseconds() const;
	NumericType GetAsSeconds() const;
	NumericType GetAsMinutes() const;
	NumericType GetAsHours() const;

	static ZtTime FromNanoseconds(NumericType Nanoseconds);
	static ZtTime FromMicroseconds(NumericType Microseconds);
	static ZtTime FromMilliseconds(NumericType Milliseconds);
	static ZtTime FromSeconds(NumericType Seconds);
	static ZtTime FromMinutes(NumericType Minutes);
	static ZtTime FromHours(NumericType Hours);

private:

	NumericType TimeAsNanoseconds = 0.f;
};