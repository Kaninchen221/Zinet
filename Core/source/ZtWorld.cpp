#include "Zinet/Core/ZtWorld.h"

void ZtWorld::BeginPlay()
{
	ZtObject::BeginPlay();
	Logger->info("{}", __FUNCTION__);

	Level.BeginPlay();
}

void ZtWorld::Tick(float DeltaTime)
{
	ZtObject::Tick(DeltaTime);

	Level.Tick(DeltaTime);
}

void ZtWorld::EndPlay()
{
	ZtObject::EndPlay();
	Logger->info("{}", __FUNCTION__);

	Level.EndPlay();
}

ZtLevel& ZtWorld::GetLevel()
{
	return Level;
}