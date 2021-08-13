#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

class ZINET_CORE_API ZtIdentifier {
public:

    const static inline size_t Invalid = -1;

    ZtIdentifier() = delete;
    explicit ZtIdentifier(size_t Identifier);
    ZtIdentifier(ZtIdentifier & Other);
    ZtIdentifier(ZtIdentifier && Other);

    ZtIdentifier & operator = (ZtIdentifier & Other);
    ZtIdentifier & operator = (ZtIdentifier && Other);

    ~ZtIdentifier() = default;

    size_t GetUnderlyingNumber() const noexcept;

private:

    size_t UnderlyingNumber = Invalid;

};

