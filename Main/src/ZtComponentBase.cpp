#include "Zinet/Main/ECRS/ZtComponentBase.h"

namespace zt {

	ComponentBase::ComponentBase(const ComponentBase& other)
	{
		*this = other;
	}

	ComponentBase::ComponentBase(ComponentBase&& other)
	{
		*this = other;
	}

}