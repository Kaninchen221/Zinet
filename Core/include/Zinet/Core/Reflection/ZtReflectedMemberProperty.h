#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

template<typename ClassT, typename PropertyT>
class ZtReflectedMemberProperty
{

public:

	using ClassType = ClassT;
	using PropertyType = PropertyT;

	ZtReflectedMemberProperty(const ClassT& ClassObject, const PropertyT& PropertyObject);

	std::int64_t GetInternalOffset() const;

	PropertyType* GetAsPointer(const ClassT& ClassObject) const;

	PropertyType GetAsValue(const ClassT& ClassObject) const;

protected:

	std::int64_t InternalOffset;

};

template<typename ClassT, typename PropertyT>
inline ZtReflectedMemberProperty<ClassT, PropertyT>::ZtReflectedMemberProperty(const ClassT& ClassObject, const PropertyT& PropertyObject)
{
	InternalOffset = (std::int64_t)(&PropertyObject) - (std::int64_t)(&ClassObject);
}

template<typename ClassType, typename PropertyType>
inline std::int64_t ZtReflectedMemberProperty<ClassType, PropertyType>::GetInternalOffset() const
{
	return InternalOffset;
}

template<typename ClassT, typename PropertyT>
inline typename ZtReflectedMemberProperty<ClassT, PropertyT>::PropertyType* ZtReflectedMemberProperty<ClassT, PropertyT>::GetAsPointer(const ClassT& ClassObject) const
{
	std::int64_t PropertyAdressAsNumber = (std::int64_t)(&ClassObject) + InternalOffset;
	PropertyType* PropertyPointer = (PropertyType*)(PropertyAdressAsNumber);
	return PropertyPointer;
}

template<typename ClassT, typename PropertyT>
inline typename ZtReflectedMemberProperty<ClassT, PropertyT>::PropertyType ZtReflectedMemberProperty<ClassT, PropertyT>::GetAsValue(const ClassT& ClassObject) const
{
	PropertyType PropertyAsValue = *GetAsPointer(ClassObject);
	return PropertyAsValue;
}