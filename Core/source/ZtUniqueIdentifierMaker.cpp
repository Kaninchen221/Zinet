#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

namespace zt
{

    Identifier UniqueIdentifierMaker::Reserve()
    {
        std::optional<Identifier> OptionalUniqueIdentifier = TryReserveReleasedIdentifier();
        if (OptionalUniqueIdentifier)
        {
            return OptionalUniqueIdentifier.value();
        }

        Identifier Identifier = ReserveNewIdentifier();
        return std::move(Identifier);
    }

    std::optional<Identifier> UniqueIdentifierMaker::TryReserveReleasedIdentifier()
    {
        std::vector<bool>::iterator Iterator = Numbers.begin();
        for (size_t Index = 0; Index < Numbers.size(); ++Index)
        {
            bool IsReserved = *Iterator;
            if (!IsReserved)
            {
                return Identifier(Index);
            }

            ++Iterator;
        }

        return {};
    }

    Identifier UniqueIdentifierMaker::ReserveNewIdentifier()
    {
        Numbers.emplace_back(true);
        size_t NumbersSize = Numbers.size();
        size_t NumbersLastIndex = NumbersSize - 1;
        return Identifier(NumbersLastIndex);
    }

    void UniqueIdentifierMaker::Release(Identifier& Identifier)
    {
        size_t UnderlyingNumber = Identifier.GetUnderlyingNumber();
        size_t NumbersSize = Numbers.size();

        if (NumbersSize <= UnderlyingNumber)
        {
            Logger->warn("Can't release identifier with underlying number: {0} - number is out of reserved numbers", UnderlyingNumber);
            return;
        }

        auto IsReserved = Numbers[UnderlyingNumber];
        if (!IsReserved)
        {
            Logger->warn("Can't release identifier with underlying number: {0} - number is already released", UnderlyingNumber);
            return;
        }

        IsReserved = false;
    }

    bool UniqueIdentifierMaker::IsReserved(size_t UnderlyingNumber) const
    {
        if (UnderlyingNumber >= Numbers.size())
        {
            return false;
        }

        bool IsReserved = Numbers[UnderlyingNumber];
        return IsReserved;
    }

}