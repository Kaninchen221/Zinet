#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>
#include <type_traits>

template<typename MemberPointerType>
class ZtReflectedMemberProperty
{

public:

	using InternalMemberPointerType = MemberPointerType;

	constexpr ZtReflectedMemberProperty() = default;
	constexpr ZtReflectedMemberProperty(MemberPointerType MemberPointer);

	MemberPointerType GetPointer() const;

protected:

	MemberPointerType MemberPointer;

};

template<typename MemberPointerType>
inline constexpr ZtReflectedMemberProperty<MemberPointerType>::ZtReflectedMemberProperty(MemberPointerType MemberPointer)
	: MemberPointer(MemberPointer)
{
}

template<typename MemberPointerType>
inline MemberPointerType ZtReflectedMemberProperty<MemberPointerType>::GetPointer() const
{
	return MemberPointer;
}
