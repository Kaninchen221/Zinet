#pragma once

#include "Zinet/Core/ZtCoreConfig.h"
#include "Zinet/Core/ZtTime.h"

#include <string>
#include <source_location>
#include <typeinfo>

namespace zt::core
{
	struct ZINET_CORE_API ReflectedData
	{
		std::string name;
		std::string typeName;
		void* address = nullptr;
	};

	class ZINET_CORE_API ReflectionSystem {

	public:

		ReflectionSystem() = default;
		ReflectionSystem(const ReflectionSystem& other) = default;
		ReflectionSystem(ReflectionSystem&& other) = default;

		ReflectionSystem& operator = (const ReflectionSystem& other) = default;
		ReflectionSystem& operator = (ReflectionSystem&& other) = default;

		~ReflectionSystem() = default;

		static ReflectedData Reflect(auto& something, const std::string& name);

	private:

	};

	ReflectedData ReflectionSystem::Reflect(auto& something, const std::string& name)
	{
		std::source_location sourceLocation = std::source_location::current();

		ReflectedData result;
		result.name = name;

		const std::type_info& typeInfo = typeid(something);
		result.typeName = typeInfo.name();

		result.address = &something;

		return result;
	}
}