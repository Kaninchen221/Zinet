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
			: name{ newName }, functions{ newFunctions } {}

		ReflectedClass& operator = (const ReflectedClass& other) = default;
		ReflectedClass& operator = (ReflectedClass&& other) = default;

		~ReflectedClass() noexcept = default;

		constexpr std::string_view getName() const { return name; }

		template<class MemberFunctionAddress>
		constexpr auto function(MemberFunctionAddress functionAddress, std::string_view functionName)
		{ 
			std::tuple<FunctionData<MemberFunctionAddress>> newFunction{{functionAddress, functionName}};
			auto functionsAfterConcat = std::tuple_cat(functions, newFunction);
			ReflectedClass<decltype(functionsAfterConcat)> result{name, functionsAfterConcat};
			return result;
		}

		constexpr auto* getFunctionByName(std::string_view functionName)
		{
			return static_cast<FunctionData<FunctionAddressPlaceholder>*>(nullptr);
		}

		template<size_t index>
		constexpr auto* getFunctionByIndex()
		{
			return static_cast<FunctionData<FunctionAddressPlaceholder>*>(nullptr);
		}

	protected:

		std::string_view name;
		FunctionsT functions;

	};

}