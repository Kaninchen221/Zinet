#pragma once

#include "Zinet/Core/ZtCore.h"

class ZINET_CORE_API ZtSystem
{

public:

    ZtSystem() = default;
    ZtSystem(const ZtSystem& Other) = default;
    ZtSystem(ZtSystem&& Other) = default;

    ZtSystem& operator = (const ZtSystem& Other) = default;
    ZtSystem& operator = (ZtSystem&& Other) = default;

    virtual ~ZtSystem() noexcept = default;



};