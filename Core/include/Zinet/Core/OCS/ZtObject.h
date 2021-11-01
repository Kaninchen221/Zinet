#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtTypes.h"
#include "Zinet/Core/ZtBeginPlayReason.h"
#include "Zinet/Core/ZtEndPlayReason.h"

class ZINET_CORE_API ZtObject
{

public:

    ZtObject() = default;
    ZtObject(const ZtObject& Other) = default;
    ZtObject(ZtObject&& Other) = default;

    ZtObject& operator = (const ZtObject& Other) = default;
    ZtObject& operator = (ZtObject&& Other) = default;

    virtual ~ZtObject() noexcept = default;

    virtual void BeginPlay(ZtBeginPlayReason Reason);

    virtual void EndPlay(ZtEndPlayReason Reason);

    virtual void Tick(ZtFloat DeltaTime);

    ZtBool GetShouldTick() const;

    void SetShouldTick(ZtBool Value);

protected:

    ZtBool bShouldTick = false;

};