#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtUniqueIdentifier.h"

class ZINET_CORE_API ZtUniqueIdentifierMaker
{

public:

    ZtUniqueIdentifier Reserve();

protected:

    std::vector<bool> Numbers;

};