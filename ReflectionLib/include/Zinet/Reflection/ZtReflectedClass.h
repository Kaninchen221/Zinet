#pragma once

#include "Zinet/Reflection/ZtReflection.h"

namespace zt::reflection
{
	template<class FunctionAddressT = void(*)()>
	struct ZINET_REFLECTION_LAYER_API FunctionData
	{
		using FunctionAddress = FunctionAddressT;

		FunctionAddress address = nullptr;
		std::string_view name;
	};

	template<class FunctionsType = std::tuple<>>
	class ZINET_REFLECTION_LAYER_API ReflectedClass
	{

	public:

		using FunctionsT = FunctionsType;

		ReflectedClass() = default;
		ReflectedClass(const ReflectedClass& other) = default;
		ReflectedClass(ReflectedClass&& other) = default;

		ReflectedClass(std::string_view newName) : name{newName} {}

		ReflectedClass& operator = (const ReflectedClass& other) = default;
		ReflectedClass& operator = (ReflectedClass&& other) = default;

		~ReflectedClass() noexcept = default;

		constexpr std::string_view getName() const { return name; }

		template<class MemberFunctionAddress>
		constexpr auto function(MemberFunctionAddress functionAddress, std::string_view functionName)
			-> ReflectedClass<decltype(std::tuple_cat<FunctionsT, std::tuple<FunctionData<MemberFunctionAddress>>>({}, {}))>
		{ 
			//return std::tuple_cat(functions, std::tuple<MemberFunctionT>{}); 
			return {};
		}

	protected:

		std::string_view name;
		FunctionsT functions;

	};

}