#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtBeginPlayReason.h"
#include "Zinet/Core/ZtEndPlayReason.h"

namespace zt
{

    class ZINET_CORE_API Object
    {

    public:

        Object() = default;
        Object(const Object& Other) = default;
        Object(Object&& Other) = default;

        Object& operator = (const Object& Other) = default;
        Object& operator = (Object&& Other) = default;

        virtual ~Object() noexcept = default;

        virtual void BeginPlay(BeginPlayReason Reason);

        virtual void EndPlay(EndPlayReason Reason);

        virtual void Tick(float DeltaTime);

        bool GetShouldTick() const;

        void SetShouldTick(bool Value);

    protected:

        bool bShouldTick = false;

    };

}