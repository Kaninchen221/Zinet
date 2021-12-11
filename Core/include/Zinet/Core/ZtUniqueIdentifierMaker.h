#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtIdentifier.h"
#include "Zinet/Core/ZtLogger.h"

#include <type_traits>
#include <vector>

namespace zt
{

    class ZINET_CORE_API UniqueIdentifierMaker
    {
        static inline Logger::SimpleConsoleLogger Logger = Logger::CreateSimpleConsoleLogger("UniqueIdentifierMaker");

    public:

        Identifier Reserve();

        void Release(Identifier& UniqueIdentifier);

        bool IsReserved(size_t UnderlyingNumber) const;

    protected:

        std::optional<Identifier> TryReserveReleasedIdentifier();

        Identifier ReserveNewIdentifier();

        std::vector<bool> Numbers;

    };

}