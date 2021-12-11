#include "Zinet/Core/ZtIdentifier.h"

namespace zt
{

    Identifier::Identifier(size_t Identifier)
    {
        UnderlyingNumber = Identifier;
    }

    size_t Identifier::GetUnderlyingNumber() const noexcept
    {
        return UnderlyingNumber;
    }

    Identifier::Identifier(Identifier& Other)
    {
        *this = Other;
    }

    Identifier& Identifier::operator=(Identifier& Other)
    {
        UnderlyingNumber = Other.UnderlyingNumber;
        Other.UnderlyingNumber = Invalid;
        return *this;
    }

    Identifier::Identifier(Identifier&& Other)
    {
        *this = Other;
    }

    Identifier& Identifier::operator=(Identifier&& Other)
    {
        return *this;
    }

}