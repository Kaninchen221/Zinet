#pragma once

#include "Zinet/Reflection/ZtReflection.h"

#include <any>
#include <iostream>

namespace zt::reflection
{
	template<class FunctionAddressT = void(*)()>
	struct ZINET_REFLECTION_LAYER_API FunctionData
	{
		using FunctionAddress = FunctionAddressT;

		FunctionAddress address = nullptr;
		std::string_view name;
	};

	template<class Functions = std::tuple<>>
	class ZINET_REFLECTION_LAYER_API ReflectedClass
	{

	public:

		using FunctionsT = Functions;
		typedef void(*FunctionAddressPlaceholder)();

		ReflectedClass() = default;
		ReflectedClass(const ReflectedClass& other) = default;
		ReflectedClass(ReflectedClass&& other) = default;

		ReflectedClass(std::string_view newName, const FunctionsT& newFunctions) 
			: className{ newName }, functions{ newFunctions } {}

		ReflectedClass& operator = (const ReflectedClass& other) = default;
		ReflectedClass& operator = (ReflectedClass&& other) = default;

		~ReflectedClass() noexcept = default;

		constexpr std::string_view getName() const { return className; }

		template<class MemberFunctionAddress>
		constexpr auto function(MemberFunctionAddress functionAddress, std::string_view functionName)
		{ 
			std::tuple<FunctionData<MemberFunctionAddress>> newFunction{{functionAddress, functionName}};
			auto functionsAfterConcat = std::tuple_cat(functions, newFunction);
			ReflectedClass<decltype(functionsAfterConcat)> result{className, functionsAfterConcat};
			return result;
		}

		constexpr auto* getFunctionByName(std::string_view functionName)
		{
			std::any result;
			//auto callable = [&result, const &functionName](auto&&... args) {};

			//std::apply([&result, const& functionName](auto&&... args) {}, functions);
			auto tuple = std::make_tuple(1, 2, 3);
			std::apply(
				[](auto&&... args) 
				{
					((if (args == 1) std::cout << args << '\n'), ...);
				}, tuple);

			return static_cast<FunctionData<FunctionAddressPlaceholder>*>(nullptr);
		}

		template<size_t Index>
		constexpr auto* getFunctionByIndex()
		{
			if constexpr (Index < std::tuple_size<FunctionsT>{})
				return &std::get<Index>(functions);
			else
				return static_cast<FunctionData<FunctionAddressPlaceholder>*>(nullptr);
		}

	protected:

		std::string_view className;
		FunctionsT functions;

	};

}