#pragma once

#include "Zinet/Core/ZtCore.h"

#include <cstdint>

namespace zt
{

    class ZINET_CORE_API Identifier {
    public:

        const static inline size_t Invalid = -1;

        Identifier() = delete;
        explicit Identifier(size_t Identifier);
        Identifier(Identifier& Other);
        Identifier(Identifier&& Other);

        Identifier& operator = (Identifier& Other);
        Identifier& operator = (Identifier&& Other);

        ~Identifier() = default;

        size_t GetUnderlyingNumber() const noexcept;

    private:

        size_t UnderlyingNumber = Invalid;

    };

}