#pragma once

#include "Zinet/Core/ZtLevel.h"
#include "Zinet/Core/ZtLogger.h"

class ZtWorld
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtWorld");

public:

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual void EndPlay();

	ZtLevel& GetLevel();

protected:

	ZtLevel Level;

};