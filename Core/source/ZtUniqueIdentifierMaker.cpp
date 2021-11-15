#include "Zinet/Core/ZtUniqueIdentifierMaker.h"

ZtIdentifier ZtUniqueIdentifierMaker::Reserve()
{
    std::optional<ZtIdentifier> OptionalUniqueIdentifier = TryReserveReleasedIdentifier();
    if(OptionalUniqueIdentifier)
    {
        return OptionalUniqueIdentifier.value();
    }

    ZtIdentifier Identifier = ReserveNewIdentifier();
    return std::move(Identifier);
}

std::optional<ZtIdentifier> ZtUniqueIdentifierMaker::TryReserveReleasedIdentifier()
{
    std::vector<bool>::iterator Iterator = Numbers.begin();
    for(size_t Index = 0; Index < Numbers.size(); ++Index)
    {
        bool IsReserved = *Iterator;
        if(!IsReserved)
        {
            return ZtIdentifier(Index);
        }

        ++Iterator;
    }

    return {};
}

ZtIdentifier ZtUniqueIdentifierMaker::ReserveNewIdentifier()
{
    Numbers.emplace_back(true);
    size_t NumbersSize = Numbers.size();
    size_t NumbersLastIndex = NumbersSize - 1;
    return ZtIdentifier(NumbersLastIndex);
}

void ZtUniqueIdentifierMaker::Release(ZtIdentifier& Identifier)
{
    size_t UnderlyingNumber = Identifier.GetUnderlyingNumber();
    size_t NumbersSize = Numbers.size();

    if(NumbersSize <= UnderlyingNumber)
    {
        Logger->warn("Can't release identifier with underlying number: {0} - number is out of reserved numbers", UnderlyingNumber);
        return;
    }

    auto IsReserved = Numbers[UnderlyingNumber];
    if(!IsReserved)
    {
        Logger->warn("Can't release identifier with underlying number: {0} - number is already released", UnderlyingNumber);
        return;
    }

    IsReserved = false;
}

bool ZtUniqueIdentifierMaker::IsReserved(size_t UnderlyingNumber) const
{
    if(UnderlyingNumber >= Numbers.size())
    {
        return false;
    }

    bool IsReserved = Numbers[UnderlyingNumber];
    return IsReserved;
}
