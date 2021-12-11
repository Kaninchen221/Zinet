#pragma once

#include <tuple>
#include <utility>

namespace zt
{

    template<typename MemberPointerType>
    class ReflectedMemberProperty;

    template<typename FunctionPointerType>
    class ReflectedMemberFunction;

    template<typename First, typename Second>
    using ConcatTwoTupleTypes = decltype(std::tuple_cat<First, Second>(First(), Second()));

    template<typename MemberPropertyPointerType>
    using MakePropertyTuple = std::tuple<ReflectedMemberProperty<MemberPropertyPointerType>>;

    template<typename MemberFunctionPointerType>
    using MakeFunctionTuple = std::tuple<ReflectedMemberFunction<MemberFunctionPointerType>>;

    template<typename ReflectedClassType>
    using MakeReflectedClassTuple = std::tuple<ReflectedClassType>;

    template<typename TupleType, typename CallableType>
    constexpr void ApplyToTuple(TupleType& Tuple, const CallableType& Callable);

    template<typename TupleType, typename CallableType, typename NumberType, NumberType... Numbers>
    constexpr void ApplyToTupleInternal(TupleType& Tuple, const CallableType& Callable,
        const std::integer_sequence<NumberType, Numbers...>& NumberSequence);

}

#include "ZtReflectionUtilities.inl"