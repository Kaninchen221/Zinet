#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

class ZINET_CORE_API ZtIdentifier {
public:

    const static inline ZtSize Invalid = -1;

    ZtIdentifier() = delete;
    explicit ZtIdentifier(ZtSize Identifier);
    ZtIdentifier(ZtIdentifier& Other);
    ZtIdentifier(ZtIdentifier&& Other);

    ZtIdentifier& operator = (ZtIdentifier& Other);
    ZtIdentifier& operator = (ZtIdentifier&& Other);

    ~ZtIdentifier() = default;

    ZtSize GetUnderlyingNumber() const noexcept;

private:

    ZtSize UnderlyingNumber = Invalid;

};

