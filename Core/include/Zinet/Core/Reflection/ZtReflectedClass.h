#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

#include <tuple>

namespace zt
{

	template<typename ClassType, typename MemberPropertiesTupleType = std::tuple<>, typename MemberFunctionsTupleType = std::tuple<>>
	class ReflectedClass
	{

	protected:

		MemberPropertiesTupleType ReflectedMemberProperties;
		MemberFunctionsTupleType ReflectedMemberFunctions;

	public:

		constexpr ReflectedClass() = default;
		constexpr ReflectedClass(const MemberPropertiesTupleType& ReflectedMemberProperties, const MemberFunctionsTupleType& ReflectedMemberFunctions)
			: ReflectedMemberProperties(ReflectedMemberProperties), ReflectedMemberFunctions(ReflectedMemberFunctions)
		{
		}

		template<typename MemberPropertyPointerType>
		constexpr ReflectedClass<ClassType, ConcatTwoTupleTypes<MemberPropertiesTupleType, MakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionsTupleType>
			RegisterProperty(MemberPropertyPointerType MemberPropertyPointer);

		template<typename MemberFunctionPointerType>
		constexpr ReflectedClass<ClassType, MemberPropertiesTupleType, ConcatTwoTupleTypes<MemberFunctionsTupleType, MakeFunctionTuple<MemberFunctionPointerType>>>
			RegisterFunction(MemberFunctionPointerType MemberFunctionPointer);

		constexpr const MemberPropertiesTupleType& GetReflectedProperties() const;

		constexpr const MemberFunctionsTupleType& GetReflectedFunctions() const;

		constexpr explicit operator bool() const { return true; }
	};

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionTupleType>
	template<typename MemberPropertyPointerType>
	inline constexpr ReflectedClass<ClassType, ConcatTwoTupleTypes<MemberPropertiesTupleType, MakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionTupleType>
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionTupleType>::RegisterProperty(MemberPropertyPointerType MemberPropertyPointer)
	{
		return { std::tuple_cat(ReflectedMemberProperties, MakePropertyTuple<MemberPropertyPointerType>(MemberPropertyPointer)), ReflectedMemberFunctions };
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	template<typename MemberFunctionPointerType>
	inline constexpr ReflectedClass<ClassType, MemberPropertiesTupleType, ConcatTwoTupleTypes<MemberFunctionsTupleType, MakeFunctionTuple<MemberFunctionPointerType>>>
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::RegisterFunction(MemberFunctionPointerType MemberFunctionPointer)
	{
		return { ReflectedMemberProperties, std::tuple_cat(ReflectedMemberFunctions, MakeFunctionTuple<MemberFunctionPointerType>(MemberFunctionPointer)) };
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	inline constexpr const MemberPropertiesTupleType&
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::GetReflectedProperties() const
	{
		return ReflectedMemberProperties;
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	constexpr const MemberFunctionsTupleType&
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::GetReflectedFunctions() const
	{
		return ReflectedMemberFunctions;
	}

}