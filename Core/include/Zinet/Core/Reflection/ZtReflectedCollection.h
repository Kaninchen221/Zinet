#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

namespace zt
{

    template<typename ReflectedClassesTupleType = std::tuple<>>
    class ReflectedCollection
    {

    protected:

        ReflectedClassesTupleType reflectedClasses;

    public:

        constexpr ReflectedCollection() = default;
        constexpr ReflectedCollection(ReflectedClassesTupleType reflectedClasses)
            : reflectedClasses(reflectedClasses)
        {}

        template<typename ReflectedClassType>
        ReflectedCollection<ConcatTwoTupleTypes<ReflectedClassesTupleType, MakeReflectedClassTuple<ReflectedClassType>>>
            registerClass(ReflectedClassType reflectedClass);

        const ReflectedClassesTupleType& getReflectedClasses() const;

    };

    template<typename ReflectedClassesTupleType>
    template<typename ReflectedClassType>
    ReflectedCollection<ConcatTwoTupleTypes<ReflectedClassesTupleType, MakeReflectedClassTuple<ReflectedClassType>>>
        ReflectedCollection<ReflectedClassesTupleType>::registerClass(ReflectedClassType reflectedClass)
    {
        return { std::tuple_cat(reflectedClasses, MakeReflectedClassTuple<ReflectedClassType>(reflectedClass)) };
    }

    template<typename ReflectedClassesTupleType>
    const ReflectedClassesTupleType&
        ReflectedCollection<ReflectedClassesTupleType>::getReflectedClasses() const
    {
        return reflectedClasses;
    }

}