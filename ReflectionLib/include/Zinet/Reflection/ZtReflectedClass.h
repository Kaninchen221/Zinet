#pragma once

#include "Zinet/Reflection/ZtReflection.h"

namespace zt::reflection
{
	template<class FunctionsType = std::tuple<>>
	class ZINET_REFLECTION_LAYER_API ReflectedClass
	{

	public:

		using FunctionT = FunctionsType;

		ReflectedClass() = default;
		ReflectedClass(const ReflectedClass& other) = default;
		ReflectedClass(ReflectedClass&& other) = default;

		ReflectedClass(std::string_view newName) : name{newName} {}

		ReflectedClass& operator = (const ReflectedClass& other) = default;
		ReflectedClass& operator = (ReflectedClass&& other) = default;

		~ReflectedClass() noexcept = default;

		constexpr std::string_view getName() const { return name; }

		template<class MemberFunctionT>
		constexpr auto function(MemberFunctionT function, std::string_view name) 
			-> ReflectedClass<decltype(std::tuple_cat<FunctionT, std::tuple<MemberFunctionT>>({}, {}))>
		{ 
			//return std::tuple_cat(functions, std::tuple<MemberFunctionT>{}); 
			return {};
		}

	protected:

		std::string_view name;
		FunctionT functions;

	};

}