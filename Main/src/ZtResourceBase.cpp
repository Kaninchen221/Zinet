#include "Zinet/Main/ECRS/ZtResourceBase.h"

namespace zt {

	ResourceBase::ResourceBase(const ResourceBase& other)
	{
		*this = other;
	}

	ResourceBase::ResourceBase(ResourceBase&& other)
	{
		*this = other;
	}

}