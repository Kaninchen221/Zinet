#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtMainException.h"
#include "Zinet/Main/ZtTime.h"
#include "Zinet/Main/ECRS/ZtComponent.h"

namespace zt {


	template<typename ServicedTypeDerivedFromComponent>
	class ZINET_MAIN_API System {

	public:

		static constexpr bool IsServicedTypeDerivedFromComponent() noexcept;
		static_assert(IsServicedTypeDerivedFromComponent(), "ServicedType must derived from Component class");

		using ServicedType = ServicedTypeDerivedFromComponent;
		using ComponentsContainer = std::vector<ServicedTypeDerivedFromComponent>;
		using Microseconds = Time::Microseconds;

		System() = default;
		System(const System& other) = default;
		System(System&& other) = default;

		System& operator = (const System& other) = default;
		System& operator = (System&& other) = default;
		
		~System() noexcept = default;
	
		virtual void update(ComponentsContainer& components, Microseconds elapsedTime);

	};

	template<typename ServicedTypeDerivedFromComponent>
	inline constexpr bool System<ServicedTypeDerivedFromComponent>::IsServicedTypeDerivedFromComponent() noexcept
	{
		return std::is_base_of<Component, ServicedTypeDerivedFromComponent>::value;
	}

	template<typename ServicedTypeDerivedFromComponent>
	inline void System<ServicedTypeDerivedFromComponent>::update(ComponentsContainer& components, Microseconds elapsedTime)
	{
		throw MainException("Dervied class must provide own implementation of this function");
	}

}