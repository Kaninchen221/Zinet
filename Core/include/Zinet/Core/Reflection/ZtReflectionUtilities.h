#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"

#include <tuple>
#include <utility>

template<typename First, typename Second>
using ZtConcatTwoTupleTypes = decltype(std::tuple_cat<First, Second>(First(), Second()));

template<typename MemberPropertyPointerType>
using ZtMakePropertyTuple = std::tuple<ZtReflectedMemberProperty<MemberPropertyPointerType>>;

template<typename MemberFunctionPointerType>
using ZtMakeFunctionTuple = std::tuple<ZtReflectedMemberFunction<MemberFunctionPointerType>>;

template<typename TupleType, typename CallableType>
constexpr void ZtApplyToTuple(TupleType& Tuple, const CallableType& Callable);

template<typename TupleType, typename CallableType, typename NumberType, NumberType... Numbers>
constexpr void ZtApplyToTupleInternal(TupleType& Tuple, const CallableType& Callable,
                     const std::integer_sequence<NumberType, Numbers...>& NumberSequence);



#include "ZtReflectionUtilities.inl"