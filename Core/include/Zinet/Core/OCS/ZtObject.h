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
        Object(const Object& other) = default;
        Object(Object&& other) = default;

        Object& operator = (const Object& other) = default;
        Object& operator = (Object&& other) = default;

        virtual ~Object() noexcept = default;

        virtual void beginPlay(BeginPlayReason reason);

        virtual void endPlay(EndPlayReason reason);

        virtual void tick(float deltaTime);

        bool getShouldTick() const;

        void setShouldTick(bool value);

    protected:

        bool shouldTick = false;

    };

}