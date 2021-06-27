#include "Zinet/Core/ZtWorld.h"

void ZtWorld::BeginPlay()
{
	Logger->info("{}", __FUNCTION__);

}

void ZtWorld::Tick(float DeltaTime)
{

}

void ZtWorld::EndPlay()
{
	Logger->info("{}", __FUNCTION__);

}

ZtLevel& ZtWorld::GetLevel()
{
	return Level;
}