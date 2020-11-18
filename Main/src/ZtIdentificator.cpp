#include "Zinet/Main/ZtIdentificator.h"

namespace zt {

	Identificator::Identificator(size_t identificatorNumber) noexcept
		: number(identificatorNumber)
	{}

	bool Identificator::operator==(const Identificator& other) const noexcept
	{
		return (this->number == other.number);
	}

	bool Identificator::operator!=(const Identificator& other) const noexcept
	{
		return (this->number != other.number);
	}

	size_t Identificator::getNumber() const noexcept
	{
		return number;
	}

}