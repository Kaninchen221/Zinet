#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

template<typename ClassType, typename MemberPropertiesTupleType = std::tuple<>, typename MemberFunctionsTupleType = std::tuple<>>
class ZtReflectedClass
{

protected:

	MemberPropertiesTupleType ReflectedMemberProperties;
	MemberFunctionsTupleType ReflectedMemberFunctions;

public:

	constexpr ZtReflectedClass() = default;
	constexpr ZtReflectedClass(const MemberPropertiesTupleType& ReflectedMemberProperties, const MemberFunctionsTupleType& ReflectedMemberFunctions)
		: ReflectedMemberProperties(ReflectedMemberProperties), ReflectedMemberFunctions(ReflectedMemberFunctions)
	{
	}

	template<typename MemberPropertyPointerType>
	constexpr ZtReflectedClass<ClassType, ZtConcatTwoTupleTypes<MemberPropertiesTupleType, ZtMakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionsTupleType>
		RegisterProperty(MemberPropertyPointerType MemberPropertyPointer);

	template<typename MemberFunctionPointerType>
	constexpr ZtReflectedClass<ClassType, MemberPropertiesTupleType, ZtConcatTwoTupleTypes<MemberFunctionsTupleType, ZtMakeFunctionTuple<MemberFunctionPointerType>>>
		RegisterFunction(MemberFunctionPointerType MemberFunctionPointer);

	constexpr const MemberPropertiesTupleType& GetReflectedProperties() const;

	constexpr const MemberFunctionsTupleType& GetReflectedFunctions() const;

	constexpr explicit operator bool() const { return true; }
};

template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionTupleType>
template<typename MemberPropertyPointerType>
inline constexpr ZtReflectedClass<ClassType, ZtConcatTwoTupleTypes<MemberPropertiesTupleType, ZtMakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionTupleType>
ZtReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionTupleType>::RegisterProperty(MemberPropertyPointerType MemberPropertyPointer)
{
	return { std::tuple_cat(ReflectedMemberProperties, ZtMakePropertyTuple<MemberPropertyPointerType>(MemberPropertyPointer)), ReflectedMemberFunctions };
}

template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
template<typename MemberFunctionPointerType>
inline constexpr ZtReflectedClass<ClassType, MemberPropertiesTupleType, ZtConcatTwoTupleTypes<MemberFunctionsTupleType, ZtMakeFunctionTuple<MemberFunctionPointerType>>>
ZtReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::RegisterFunction(MemberFunctionPointerType MemberFunctionPointer)
{
	return { ReflectedMemberProperties, std::tuple_cat(ReflectedMemberFunctions, ZtMakeFunctionTuple<MemberFunctionPointerType>(MemberFunctionPointer)) };
}

template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
inline constexpr const MemberPropertiesTupleType&
ZtReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::GetReflectedProperties() const
{
	return ReflectedMemberProperties;
}

template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
constexpr const MemberFunctionsTupleType&
ZtReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::GetReflectedFunctions() const
{
    return ReflectedMemberFunctions;
}
