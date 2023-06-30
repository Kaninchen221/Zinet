#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"
#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

#include <tuple>

namespace zt::core
{

	template<typename ClassType, typename MemberPropertiesTupleType = std::tuple<>, typename MemberFunctionsTupleType = std::tuple<>>
	class ReflectedClass
	{

	protected:

		MemberPropertiesTupleType reflectedMemberProperties;
		MemberFunctionsTupleType reflectedMemberFunctions;

	public:

		constexpr ReflectedClass() = default;
		constexpr ReflectedClass(const MemberPropertiesTupleType& reflectedMemberProperties, const MemberFunctionsTupleType& reflectedMemberFunctions)
			: reflectedMemberProperties(reflectedMemberProperties), reflectedMemberFunctions(reflectedMemberFunctions)
		{
		}

		template<typename MemberPropertyPointerType>
		constexpr ReflectedClass<ClassType, ConcatTwoTupleTypes<MemberPropertiesTupleType, MakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionsTupleType>
			registerProperty(MemberPropertyPointerType memberPropertyPointer);

		template<typename MemberFunctionPointerType>
		constexpr ReflectedClass<ClassType, MemberPropertiesTupleType, ConcatTwoTupleTypes<MemberFunctionsTupleType, MakeFunctionTuple<MemberFunctionPointerType>>>
			registerFunction(MemberFunctionPointerType memberFunctionPointer);

		constexpr const MemberPropertiesTupleType& getReflectedProperties() const;

		constexpr const MemberFunctionsTupleType& getReflectedFunctions() const;

		constexpr explicit operator bool() const { return true; }
	};

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionTupleType>
	template<typename MemberPropertyPointerType>
	inline constexpr ReflectedClass<ClassType, ConcatTwoTupleTypes<MemberPropertiesTupleType, MakePropertyTuple<MemberPropertyPointerType>>, MemberFunctionTupleType>
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionTupleType>::registerProperty(MemberPropertyPointerType memberPropertyPointer)
	{
		return { std::tuple_cat(reflectedMemberProperties, MakePropertyTuple<MemberPropertyPointerType>(memberPropertyPointer)), reflectedMemberFunctions };
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	template<typename MemberFunctionPointerType>
	inline constexpr ReflectedClass<ClassType, MemberPropertiesTupleType, ConcatTwoTupleTypes<MemberFunctionsTupleType, MakeFunctionTuple<MemberFunctionPointerType>>>
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::registerFunction(MemberFunctionPointerType memberFunctionPointer)
	{
		return { reflectedMemberProperties, std::tuple_cat(reflectedMemberFunctions, MakeFunctionTuple<MemberFunctionPointerType>(memberFunctionPointer)) };
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	inline constexpr const MemberPropertiesTupleType&
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::getReflectedProperties() const
	{
		return reflectedMemberProperties;
	}

	template<typename ClassType, typename MemberPropertiesTupleType, typename MemberFunctionsTupleType>
	constexpr const MemberFunctionsTupleType&
		ReflectedClass<ClassType, MemberPropertiesTupleType, MemberFunctionsTupleType>::getReflectedFunctions() const
	{
		return reflectedMemberFunctions;
	}

}