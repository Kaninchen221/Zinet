#pragma once

#include "Zinet/Core/Reflection/ZtReflectionUtilities.h"

template<typename ReflectedClassesTupleType = std::tuple<>>
class ZtReflectedCollection
{

protected:

    ReflectedClassesTupleType ReflectedClasses;

public:

    constexpr ZtReflectedCollection() = default;
    constexpr ZtReflectedCollection(ReflectedClassesTupleType ReflectedClasses)
        : ReflectedClasses(ReflectedClasses)
    {}

    template<typename ReflectedClassType>
    ZtReflectedCollection<ZtConcatTwoTupleTypes<ReflectedClassesTupleType, ZtMakeReflectedClassTuple<ReflectedClassType>>>
            RegisterClass(ReflectedClassType ReflectedClass);

    const ReflectedClassesTupleType& GetReflectedClasses() const;

};

template<typename ReflectedClassesTupleType>
template<typename ReflectedClassType>
ZtReflectedCollection<ZtConcatTwoTupleTypes<ReflectedClassesTupleType, ZtMakeReflectedClassTuple<ReflectedClassType>>>
ZtReflectedCollection<ReflectedClassesTupleType>::RegisterClass(ReflectedClassType ReflectedClass)
{
    return { std::tuple_cat(ReflectedClasses, ZtMakeReflectedClassTuple<ReflectedClassType>(ReflectedClass)) };
}

template<typename ReflectedClassesTupleType>
const ReflectedClassesTupleType&
ZtReflectedCollection<ReflectedClassesTupleType>::GetReflectedClasses() const
{
    return ReflectedClasses;
}
