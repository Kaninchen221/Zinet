#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtIdentifier.h"
#include "Zinet/Core/ZtLogger.h"

#include <type_traits>
#include <vector>

class ZINET_CORE_API ZtUniqueIdentifierMaker
{
    static inline ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtUniqueIdentifierMaker");

public:

    ZtIdentifier Reserve();

    void Release(ZtIdentifier& UniqueIdentifier);

    ZtBool IsReserved(ZtSize UnderlyingNumber) const;

protected:

    std::optional<ZtIdentifier> TryReserveReleasedIdentifier();

    ZtIdentifier ReserveNewIdentifier();

    std::vector<ZtBool> Numbers;

};