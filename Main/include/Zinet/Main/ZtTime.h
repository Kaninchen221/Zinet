#pragma once

#include "ZtMainConfig.h"

namespace zt {

	class ZINET_MAIN_API Time {

	public:

		using UnderlyingUnsignedInteger = unsigned long long;
		using Microseconds = UnderlyingUnsignedInteger;
		using Milliseconds = UnderlyingUnsignedInteger;
		using Seconds = UnderlyingUnsignedInteger;
		using Minutes = UnderlyingUnsignedInteger;
		using Hours = UnderlyingUnsignedInteger;

		constexpr Time() noexcept;
		constexpr Time(const Time& other) noexcept = default;
		constexpr Time(Time&& other) noexcept = default;
		constexpr Time(Microseconds microseconds) noexcept;

		constexpr Time& operator = (const Time& other) noexcept = default;
		constexpr Time& operator = (Time&& other) noexcept = default;
		constexpr Time& operator = (Microseconds microseconds) noexcept;

		~Time() noexcept = default;

		constexpr Microseconds microseconds() const noexcept;
		constexpr Milliseconds milliseconds() const noexcept;
		constexpr Seconds seconds() const noexcept;
		constexpr Minutes minutes() const noexcept;
		constexpr Hours hours() const noexcept;

	private:

		Microseconds timeAsMicroseconds = 0u;
	};

}