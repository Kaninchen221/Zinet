#pragma once

#include "Zinet/Core/Reflection/ZtReflectedMemberProperty.h"
#include "Zinet/Core/Reflection/ZtReflectedMemberFunction.h"

#include <tuple>

template<typename First, typename Second>
using ZtConcatTwoTupleTypes = decltype(std::tuple_cat<First, Second>(First(), Second()));

template<typename MemberPropertyPointerType>
using ZtMakePropertyTuple = std::tuple<ZtReflectedMemberProperty<MemberPropertyPointerType>>;

template<typename MemberFunctionPointerType>
using ZtMakeFunctionTuple = std::tuple<ZtReflectedMemberFunction<MemberFunctionPointerType>>;