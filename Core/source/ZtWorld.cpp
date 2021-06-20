#include "Zinet/Core/ZtWorld.h"

void ZtWorld::BeginPlay()
{
	Logger->info("{}", __FUNCTION__);
	ZtObject::BeginPlay();
}

void ZtWorld::Tick(float DeltaTime)
{
	ZtObject::Tick(DeltaTime);
}

void ZtWorld::EndPlay()
{
	Logger->info("{}", __FUNCTION__);
	ZtObject::EndPlay();
}

ZtLevel& ZtWorld::GetLevel()
{
	return Level;
}