#pragma once

#pragma once

#include "Zinet/Core/ZtCoreConfig.h"

#include <limits>

namespace zt::core
{

	class ZINET_CORE_API UniqueID
	{
	public:

		const inline static constexpr size_t InvalidIDNumber = std::numeric_limits<size_t>::max();

		UniqueID() = default;
		UniqueID(size_t newNumber) : number{ newNumber } {}
		UniqueID(const UniqueID& other) = delete;
		UniqueID(UniqueID&& other);
		
		UniqueID& operator = (const UniqueID& other) = delete;
		UniqueID& operator = (UniqueID&& other);
		
		~UniqueID() = default;
	
		bool operator == (size_t otherNumber) const { return number == otherNumber; }

		size_t getNumber() const { return number; }

	protected:

		size_t number = InvalidIDNumber;

	};

}

