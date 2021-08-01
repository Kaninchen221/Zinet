#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

class ZINET_CORE_API ZtUniqueIdentifier
{
public:

    ZtUniqueIdentifier() = delete;
    explicit ZtUniqueIdentifier(size_t Identifier);
    ZtUniqueIdentifier(const ZtUniqueIdentifier& Other) = delete;
    ZtUniqueIdentifier(ZtUniqueIdentifier&& Other) = delete;

    ZtUniqueIdentifier& operator = (const ZtUniqueIdentifier& Other) = delete;
    ZtUniqueIdentifier& operator = (ZtUniqueIdentifier&& Other) = delete;

    ~ZtUniqueIdentifier() = default;

    size_t GetUnderlyingNumber() const noexcept;

private:

    size_t UnderlyingNumber = 0;

};

