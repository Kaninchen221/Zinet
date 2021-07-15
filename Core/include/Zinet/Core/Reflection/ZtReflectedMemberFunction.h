#pragma once

#include "Zinet/Core/ZtCore.h"
#include <type_traits>

template<typename ReturnType, typename ClassType, bool IsConst, typename ...ArgsTypes>
class ZtReflectedMemberFunction
{

public:

	using NotConstFunctionPointerType = ReturnType(ClassType::*)(ArgsTypes ...Args);
	using ConstFunctionPointerType = ReturnType(ClassType::*)(ArgsTypes ...Args) const;

	using FunctionPointerType = std::conditional_t<IsConst, ConstFunctionPointerType, NotConstFunctionPointerType>;

	using ObjectType = std::conditional_t<IsConst, const ClassType&, ClassType&>;

	void Register(FunctionPointerType FunctionPointer);

	ReturnType Invoke(ObjectType Object, ArgsTypes ...Args);

protected:

	FunctionPointerType FunctionPointer;

};

template<typename ReturnType, typename ClassType, bool IsConst, typename ...ArgsTypes>
inline void ZtReflectedMemberFunction<ReturnType, ClassType, IsConst, ArgsTypes...>::Register(FunctionPointerType FunctionPointer)
{
	this->FunctionPointer = FunctionPointer;
}

template<typename ReturnType, typename ClassType, bool IsConst, typename ...ArgsTypes>
inline ReturnType ZtReflectedMemberFunction<ReturnType, ClassType, IsConst, ArgsTypes...>::Invoke(ObjectType Object, ArgsTypes ...Args)
{
	ReturnType ReturnValue;
	ReturnValue = std::invoke(FunctionPointer, Object, Args...);

	return ReturnValue;
}