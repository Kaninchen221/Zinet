#pragma once

#include "Zinet/Core/ZtCoreConfig.h"
#include "Zinet/Core/ZtIdentifier.h"
#include "Zinet/Core/ZtLogger.h"

#include <type_traits>
#include <vector>

namespace zt::core
{

    class ZINET_CORE_API UniqueIdentifierMaker
    {
        static inline ConsoleLogger Logger = ConsoleLogger::Create("UniqueIdentifierMaker");

    public:

        Identifier reserve();

        void release(Identifier& uniqueIdentifier);

        bool isReserved(size_t underlyingNumber) const;

    protected:

        std::optional<Identifier> tryReserveReleasedIdentifier();

        Identifier reserveNewIdentifier();

        std::vector<bool> numbers;

    };

}