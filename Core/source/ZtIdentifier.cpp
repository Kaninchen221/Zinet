#include "Zinet/Core/ZtIdentifier.h"

ZtIdentifier::ZtIdentifier(size_t Identifier)
{
    UnderlyingNumber = Identifier;
}

size_t ZtIdentifier::GetUnderlyingNumber() const noexcept
{
    return UnderlyingNumber;
}

ZtIdentifier::ZtIdentifier(ZtIdentifier& Other)
{
    *this = Other;
}

ZtIdentifier &ZtIdentifier::operator=(ZtIdentifier& Other)
{
    UnderlyingNumber = Other.UnderlyingNumber;
    Other.UnderlyingNumber = Invalid;
    return *this;
}

ZtIdentifier::ZtIdentifier(ZtIdentifier&& Other)
{
    *this = Other;
}

ZtIdentifier& ZtIdentifier::operator=(ZtIdentifier&& Other)
{
    return *this;
}
