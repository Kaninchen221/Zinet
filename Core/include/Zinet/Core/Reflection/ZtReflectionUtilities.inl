#pragma once

#include <utility>
#include "ZtReflectionUtilities.h"

template<typename TupleType, typename CallableType>
constexpr void ZtApplyToTuple(TupleType& Tuple, const CallableType& Callable)
{
    constexpr size_t TupleSize = std::tuple_size_v<TupleType>;
    auto IntegerSequence = std::make_integer_sequence<size_t, TupleSize>{};

    ZtApplyToTupleInternal(Tuple, Callable, IntegerSequence);
}

template<typename TupleType, typename CallableType, typename NumberType, NumberType... Numbers>
constexpr void ZtApplyToTupleInternal(TupleType &Tuple, const CallableType &Callable,
                     const std::integer_sequence<NumberType, Numbers...>& NumberSequence)
{
    (Callable(std::get<Numbers>(Tuple)), ...);
}
