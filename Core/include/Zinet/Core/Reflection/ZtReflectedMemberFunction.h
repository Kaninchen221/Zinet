#pragma once

#include "Zinet/Core/ZtCore.h"
#include <type_traits>

namespace zt
{

	template<typename FunctionPointerType>
	class ReflectedMemberFunction
	{

	public:

		constexpr ReflectedMemberFunction() = default;
		constexpr ReflectedMemberFunction(const FunctionPointerType& FunctionPointer);

		FunctionPointerType GetPointer() const;

	protected:

		FunctionPointerType FunctionPointer;

	};

	template<typename FunctionPointerType>
	inline constexpr ReflectedMemberFunction<FunctionPointerType>::ReflectedMemberFunction(const FunctionPointerType& FunctionPointer)
		: FunctionPointer(FunctionPointer)
	{
	}

	template<typename FunctionPointerType>
	inline FunctionPointerType ReflectedMemberFunction<FunctionPointerType>::GetPointer() const
	{
		return FunctionPointer;
	}

}