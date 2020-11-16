#include "Zinet/Main/ECRS/ZtEntity.h"

#include "Zinet/Main/ZtMainException.h"
#include "Zinet/Main/ZtLogger.h"

namespace zt {

	Entity::Entity(Identificator identificator) noexcept
		: identificator(identificator)
	{
	}

	Identificator Entity::getIdentificator() const noexcept
	{
		return identificator;
	}

}