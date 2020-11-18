#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtMainException.h"
#include "Zinet/Main/ZtLogger.h"
#include "Zinet/Main/ECRS/ZtSystem.h"

#include <tuple>
#include <optional>

namespace zt {

	template<typename ... SystemTypes>
	class ZINET_MAIN_API SystemManager {

		static constexpr bool AreTypesDerivedFromSystem() noexcept;
		static_assert(AreTypesDerivedFromSystem(), "All SystemTypes must derived from System class");

		template<typename SystemDerivedClass>
		static constexpr bool IsOneOfSystemTypes() noexcept;

		template<typename SystemDerivedClass>
		static constexpr void MustBeOneOfSystemTypes() noexcept;

		template<typename T>
		using LazyInitialization = std::optional<T>;

	public:

		template<typename SystemDerivedClass>
		void active();

		template<typename SystemDerivedClass>
		bool isActive() const;

		template<typename SystemDerivedClass>
		void deactivate();

		template<typename SystemDerivedClass>
		void update(typename SystemDerivedClass::ComponentsContainer& components, typename SystemDerivedClass::Microseconds elapsedTime);

	private:

		template<typename SystemDerivedClass>
		bool isActive(const LazyInitialization<SystemDerivedClass>& system) const noexcept;

		template<typename SystemDerivedClass>
		LazyInitialization<SystemDerivedClass>& getLazyInitializationSystem();

		template<typename SystemDerivedClass>
		const LazyInitialization<SystemDerivedClass>& getLazyInitializationSystem() const;

		std::tuple<
			LazyInitialization<SystemTypes> ...
		> systems;

	};

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline constexpr bool SystemManager<SystemTypes ...>::IsOneOfSystemTypes() noexcept
	{
		return ((std::is_same<SystemDerivedClass, SystemTypes>::value) | ...);
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline constexpr void SystemManager<SystemTypes ...>::MustBeOneOfSystemTypes() noexcept
	{
		static_assert(IsOneOfSystemTypes<SystemDerivedClass>(), 
			"SystemDerivedClass must be on of the SystemTypes");
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline void SystemManager<SystemTypes ...>::active()
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		auto& system = getLazyInitializationSystem<SystemDerivedClass>();

		system = SystemDerivedClass();
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline bool SystemManager<SystemTypes ...>::isActive() const
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		auto& system = getLazyInitializationSystem<SystemDerivedClass>();

		return system.has_value();
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline void SystemManager<SystemTypes ...>::deactivate()
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		auto& system = getLazyInitializationSystem<SystemDerivedClass>();

		system = std::nullopt;
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline void SystemManager<SystemTypes ...>::update(typename SystemDerivedClass::ComponentsContainer& components, typename SystemDerivedClass::Microseconds elapsedTime)
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		auto& system = getLazyInitializationSystem<SystemDerivedClass>();

		if (isActive(system)) {
			system->update(components, elapsedTime);
		}
		else {
			std::string systemTypeAsString = typeid(SystemDerivedClass).name();
			std::string exceptionString = "System '" + systemTypeAsString + "' is deactivated";
			throw MainException(exceptionString);
		}
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline bool SystemManager<SystemTypes ...>::isActive(const LazyInitialization<SystemDerivedClass>& system) const noexcept
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		return system.has_value();
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline SystemManager<SystemTypes ...>::LazyInitialization<SystemDerivedClass>& SystemManager<SystemTypes ...>::getLazyInitializationSystem()
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		return std::get<LazyInitialization<SystemDerivedClass>>(systems);
	}

	template<typename ...SystemTypes>
	template<typename SystemDerivedClass>
	inline const SystemManager<SystemTypes ...>::LazyInitialization<SystemDerivedClass>& SystemManager<SystemTypes ...>::getLazyInitializationSystem() const
	{
		MustBeOneOfSystemTypes<SystemDerivedClass>();

		return std::get<LazyInitialization<SystemDerivedClass>>(systems);
	}

	template<typename ...SystemTypes>
	inline constexpr bool SystemManager<SystemTypes ...>::AreTypesDerivedFromSystem() noexcept
	{
		return (std::is_base_of_v<System<SystemTypes::ServicedType>, SystemTypes> && ...);
	}

}