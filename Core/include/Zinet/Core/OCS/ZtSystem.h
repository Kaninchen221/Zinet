#pragma once

#include "Zinet/Core/ZtCore.h"

namespace zt
{

    class ZINET_CORE_API System
    {

    public:

        System() = default;
        System(const System& other) = default;
        System(System&& other) = default;

        System& operator = (const System& other) = default;
        System& operator = (System&& other) = default;

        virtual ~System() noexcept = default;

    };

}