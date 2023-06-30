#pragma once

#include "Zinet/Core/ZtCore.h"

#include <type_traits>

namespace zt::core
{

	template<typename FunctionPointerType>
	class ReflectedMemberFunction
	{

	public:

		constexpr ReflectedMemberFunction() = default;
		constexpr ReflectedMemberFunction(const FunctionPointerType& functionPointer);

		FunctionPointerType getPointer() const;

	protected:

		FunctionPointerType functionPointer;

	};

	template<typename FunctionPointerType>
	inline constexpr ReflectedMemberFunction<FunctionPointerType>::ReflectedMemberFunction(const FunctionPointerType& functionPointer)
		: functionPointer(functionPointer)
	{
	}

	template<typename FunctionPointerType>
	inline FunctionPointerType ReflectedMemberFunction<FunctionPointerType>::getPointer() const
	{
		return functionPointer;
	}

}