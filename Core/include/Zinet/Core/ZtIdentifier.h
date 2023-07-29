#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

namespace zt::core
{
    class ZINET_CORE_API Identifier {
    public:

        const static inline size_t Invalid = size_t{}-1u;

        Identifier() = delete;
        explicit Identifier(size_t identifier);
        Identifier(Identifier& other);
        Identifier(Identifier&& other);

        Identifier& operator = (Identifier& other);
        Identifier& operator = (Identifier&& other);

        ~Identifier() = default;

        size_t getUnderlyingNumber() const noexcept;

    private:

        size_t underlyingNumber = Invalid;

    };

}