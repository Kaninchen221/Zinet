#pragma once

#include <utility>
#include "ZtReflectionUtilities.h"

namespace zt
{

    template<typename TupleType, typename CallableType>
    constexpr void ApplyToTuple(TupleType& tuple, const CallableType& callable)
    {
        constexpr size_t TupleSize = std::tuple_size_v<TupleType>;
        auto integerSequence = std::make_integer_sequence<size_t, TupleSize>{};

        ApplyToTupleInternal(tuple, callable, integerSequence);
    }

    template<typename TupleType, typename CallableType, typename NumberType, NumberType... Numbers>
    constexpr void ApplyToTupleInternal(TupleType& tuple, const CallableType& callable,
        const std::integer_sequence<NumberType, Numbers...>& numberSequence)
    {
        (callable(std::get<Numbers>(tuple)), ...);
    }

}