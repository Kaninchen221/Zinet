#pragma once

#include "Zinet/Reflection/ZtReflection.h"
#include "Zinet/Reflection/ZtReflectedClass.h"

#include <string>
#include <vector>
#include <ranges>

namespace zt::reflection
{
	class ZINET_REFLECTION_LAYER_API Module
	{

	public:

		Module() = default;
		Module(const Module& other) = default;
		Module(Module&& other) = default;

		Module& operator = (const Module& other) = default;
		Module& operator = (Module&& other) = default;

		~Module() noexcept = default;

		template<class T>
		constexpr ReflectedClass& reflectClass(std::string_view name);

		constexpr ReflectedClass* getReflectedClass(std::string_view name);

	protected:

		std::vector<ReflectedClass> reflectedClasses;

	};

	template<class T>
	constexpr ReflectedClass& Module::reflectClass(std::string_view name)
	{
		return reflectedClasses.emplace_back(name);
	}

	constexpr ReflectedClass* Module::getReflectedClass(std::string_view name)
	{
		for (ReflectedClass& reflectedClass : reflectedClasses)
		{
			if (reflectedClass.getName() == name)
				return &reflectedClass;
		}

		return nullptr;
	}
}
