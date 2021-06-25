#include "Zinet/Core/ZtLevel.h"

void ZtLevel::BeginPlay()
{
	ZtObject::BeginPlay();
	Logger->info("{}", __FUNCTION__);


}

void ZtLevel::Tick(float DeltaTime)
{
	ZtObject::Tick(DeltaTime);
}

void ZtLevel::EndPlay()
{
	ZtObject::EndPlay();
	Logger->info("{}", __FUNCTION__);


}
