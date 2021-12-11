#pragma once

#include <utility>
#include "ZtReflectionUtilities.h"

namespace zt
{

    template<typename TupleType, typename CallableType>
    constexpr void ApplyToTuple(TupleType& Tuple, const CallableType& Callable)
    {
        constexpr size_t TupleSize = std::tuple_size_v<TupleType>;
        auto IntegerSequence = std::make_integer_sequence<size_t, TupleSize>{};

        ApplyToTupleInternal(Tuple, Callable, IntegerSequence);
    }

    template<typename TupleType, typename CallableType, typename NumberType, NumberType... Numbers>
    constexpr void ApplyToTupleInternal(TupleType& Tuple, const CallableType& Callable,
        const std::integer_sequence<NumberType, Numbers...>& NumberSequence)
    {
        (Callable(std::get<Numbers>(Tuple)), ...);
    }

}