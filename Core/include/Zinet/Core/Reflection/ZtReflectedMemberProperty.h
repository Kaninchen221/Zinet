#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>
#include <type_traits>

namespace zt
{

	template<typename MemberPointerType>
	class ReflectedMemberProperty
	{
	
	public:
	
		using InternalMemberPointerType = MemberPointerType;
	
		constexpr ReflectedMemberProperty() = default;
		constexpr ReflectedMemberProperty(MemberPointerType MemberPointer);
	
		MemberPointerType GetPointer() const;
	
	protected:
	
		MemberPointerType MemberPointer;
	
	};
	
	template<typename MemberPointerType>
	inline constexpr ReflectedMemberProperty<MemberPointerType>::ReflectedMemberProperty(MemberPointerType MemberPointer)
		: MemberPointer(MemberPointer)
	{
	}
	
	template<typename MemberPointerType>
	inline MemberPointerType ReflectedMemberProperty<MemberPointerType>::GetPointer() const
	{
		return MemberPointer;
	}

}