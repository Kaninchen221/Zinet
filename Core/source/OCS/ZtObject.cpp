#include "Zinet/Core/OCS/ZtObject.h"

void ZtObject::BeginPlay(ZtBeginPlayReason Reason)
{

}

void ZtObject::EndPlay(ZtEndPlayReason Reason)
{

}

void ZtObject::Tick(float DeltaTime)
{

}

bool ZtObject::GetShouldTick() const
{
    return bShouldTick;
}

void ZtObject::SetShouldTick(bool Value)
{
    bShouldTick = Value;
}