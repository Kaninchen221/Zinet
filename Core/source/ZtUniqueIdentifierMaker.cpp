#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

namespace zt
{

    Identifier UniqueIdentifierMaker::reserve()
    {
        std::optional<Identifier> optionalUniqueIdentifier = tryReserveReleasedIdentifier();
        if (optionalUniqueIdentifier)
        {
            return optionalUniqueIdentifier.value();
        }

        Identifier identifier = reserveNewIdentifier();
        return std::move(identifier);
    }

    std::optional<Identifier> UniqueIdentifierMaker::tryReserveReleasedIdentifier()
    {
        //if (numbers.empty())
        //    return {};

		//for (size_t index = 0; index < numbers.size(); ++index)
		//{
		//    if (!numbers[index])
		//    {
		//        numbers[index] = true;
		//        return Identifier{ index };
		//    }
		//}

        //size_t index = 0;
        //while (true)
		//{
		//	if (!numbers[index])
		//	{
		//		numbers[index] = true;
		//		return Identifier{ index };
		//	}
        //
        //    ++index;
        //}

		size_t index = 0;
        for (std::vector<bool>::iterator iterator = numbers.begin(); iterator != numbers.end(); ++iterator)
		{
			if (!*iterator)
			{
                *iterator = true;
				return Identifier{ index };
			}

			++index;
        }

        return {};
    }

    Identifier UniqueIdentifierMaker::reserveNewIdentifier()
    {
        numbers.emplace_back(true);
        size_t numbersSize = numbers.size();
        size_t numbersLastIndex = numbersSize - 1;
        return Identifier(numbersLastIndex);
    }

    void UniqueIdentifierMaker::release(Identifier& identifier)
    {
        size_t underlyingNumber = identifier.getUnderlyingNumber();
        size_t numbersSize = numbers.size();

        if (numbersSize <= underlyingNumber)
        {
            Logger->warn("Can't release identifier with underlying number: {0} - number is out of reserved numbers", underlyingNumber);
            return;
        }

        auto isReserved = numbers[underlyingNumber];
        if (!isReserved)
        {
            Logger->warn("Can't release identifier with underlying number: {0} - number is already released", underlyingNumber);
            return;
        }

        isReserved = false;
    }

    bool UniqueIdentifierMaker::isReserved(size_t underlyingNumber) const
    {
        if (underlyingNumber >= numbers.size())
        {
            return false;
        }

        bool isReserved = numbers[underlyingNumber];
        return isReserved;
    }

}