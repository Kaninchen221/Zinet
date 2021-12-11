#include "Zinet/Core/OCS/ZtObject.h"

namespace zt
{

    void Object::BeginPlay(BeginPlayReason Reason)
    {

    }

    void Object::EndPlay(EndPlayReason Reason)
    {

    }

    void Object::Tick(float DeltaTime)
    {

    }

    bool Object::GetShouldTick() const
    {
        return bShouldTick;
    }

    void Object::SetShouldTick(bool Value)
    {
        bShouldTick = Value;
    }

}