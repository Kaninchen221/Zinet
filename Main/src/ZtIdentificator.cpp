#include "Zinet/Main/ZtIdentificator.h"

namespace zt {

	Identificator::Identificator(size_t identificatorNumber) noexcept
		: number(identificatorNumber)
	{}

	size_t Identificator::getNumber() const noexcept
	{
		return number;
	}

}