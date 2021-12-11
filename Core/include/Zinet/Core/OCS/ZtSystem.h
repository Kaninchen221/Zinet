#pragma once

#include "Zinet/Core/ZtCore.h"

namespace zt
{

    class ZINET_CORE_API System
    {

    public:

        System() = default;
        System(const System& Other) = default;
        System(System&& Other) = default;

        System& operator = (const System& Other) = default;
        System& operator = (System&& Other) = default;

        virtual ~System() noexcept = default;



    };

}