#include "Zinet/Core/ZtUniqueIdentifier.h"

ZtUniqueIdentifier::ZtUniqueIdentifier(size_t Identifier)
{
    UnderlyingNumber = Identifier;
}

size_t ZtUniqueIdentifier::GetUnderlyingNumber() const noexcept
{
    return UnderlyingNumber;
}
