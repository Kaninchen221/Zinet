#pragma once

#include "Zinet/Core/ZtCore.h"
#include <type_traits>

template<typename FunctionPointerType>
class ZtReflectedMemberFunction
{

public:

	constexpr ZtReflectedMemberFunction() = default;
	constexpr ZtReflectedMemberFunction(const FunctionPointerType& FunctionPointer);

	FunctionPointerType GetPointer() const;

protected:

	FunctionPointerType FunctionPointer;

};

template<typename FunctionPointerType>
inline constexpr ZtReflectedMemberFunction<FunctionPointerType>::ZtReflectedMemberFunction(const FunctionPointerType& FunctionPointer)
	: FunctionPointer(FunctionPointer)
{
}

template<typename FunctionPointerType>
inline FunctionPointerType ZtReflectedMemberFunction<FunctionPointerType>::GetPointer() const
{
	return FunctionPointer;
}
