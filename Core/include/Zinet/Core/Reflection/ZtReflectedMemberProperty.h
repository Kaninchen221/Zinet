#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>
#include <type_traits>

namespace zt::core
{

	template<typename MemberPointerType>
	class ReflectedMemberProperty
	{
	
	public:
	
		using InternalMemberPointerType = MemberPointerType;
	
		constexpr ReflectedMemberProperty() = default;
		constexpr ReflectedMemberProperty(MemberPointerType memberPointer);
	
		MemberPointerType getPointer() const;
	
	protected:
	
		MemberPointerType memberPointer;
	
	};
	
	template<typename MemberPointerType>
	inline constexpr ReflectedMemberProperty<MemberPointerType>::ReflectedMemberProperty(MemberPointerType memberPointer)
		: memberPointer(memberPointer)
	{
	}
	
	template<typename MemberPointerType>
	inline MemberPointerType ReflectedMemberProperty<MemberPointerType>::getPointer() const
	{
		return memberPointer;
	}

}