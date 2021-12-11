#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

namespace zt
{

    template<typename ReflectedClassesTupleType = std::tuple<>>
    class ReflectedCollection
    {

    protected:

        ReflectedClassesTupleType ReflectedClasses;

    public:

        constexpr ReflectedCollection() = default;
        constexpr ReflectedCollection(ReflectedClassesTupleType ReflectedClasses)
            : ReflectedClasses(ReflectedClasses)
        {}

        template<typename ReflectedClassType>
        ReflectedCollection<ConcatTwoTupleTypes<ReflectedClassesTupleType, MakeReflectedClassTuple<ReflectedClassType>>>
            RegisterClass(ReflectedClassType ReflectedClass);

        const ReflectedClassesTupleType& GetReflectedClasses() const;

    };

    template<typename ReflectedClassesTupleType>
    template<typename ReflectedClassType>
    ReflectedCollection<ConcatTwoTupleTypes<ReflectedClassesTupleType, MakeReflectedClassTuple<ReflectedClassType>>>
        ReflectedCollection<ReflectedClassesTupleType>::RegisterClass(ReflectedClassType ReflectedClass)
    {
        return { std::tuple_cat(ReflectedClasses, MakeReflectedClassTuple<ReflectedClassType>(ReflectedClass)) };
    }

    template<typename ReflectedClassesTupleType>
    const ReflectedClassesTupleType&
        ReflectedCollection<ReflectedClassesTupleType>::GetReflectedClasses() const
    {
        return ReflectedClasses;
    }

}