#include "Zinet/Core/OCS/ZtObject.h"

void ZtObject::BeginPlay(ZtBeginPlayReason Reason)
{

}

void ZtObject::EndPlay(ZtEndPlayReason Reason)
{

}

void ZtObject::Tick(ZtFloat DeltaTime)
{

}

ZtBool ZtObject::GetShouldTick() const
{
    return bShouldTick;
}

void ZtObject::SetShouldTick(ZtBool Value)
{
    bShouldTick = Value;
}