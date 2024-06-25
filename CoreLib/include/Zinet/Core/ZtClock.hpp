#pragma once

#include "Zinet/Core/ZtCoreConfig.hpp"
#include "Zinet/Core/ZtTime.hpp"

#include <chrono>

namespace zt::core
{
	//static_assert(false) // For some reason reflection system doesn't reflect this file
	ZT_REFLECT_CLASS() 
	class ZINET_CORE_API Clock 
	{

	public:

		//using UnderlyingClock = std::chrono::system_clock;

		//Clock() = default;
		//Clock(const Clock& other) = default;
		//Clock(Clock&& other) = default;
		//
		//Clock& operator = (const Clock& other) = default;
		//Clock& operator = (Clock&& other) = default;
		//
		//~Clock() = default;
		//
		//void start();
		//Time restart();
		//Time getElapsedTime() const;

	private:

		//UnderlyingClock::time_point savedTimePoint;

	public:
		/*GENERATED_CODE_START*/
		/*GENERATED_CODE_END*/
	};

}