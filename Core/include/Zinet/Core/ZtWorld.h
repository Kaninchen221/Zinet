#pragma once

#include "Zinet/Core/ZtObject.h"
#include "Zinet/Core/ZtLevel.h"
#include "Zinet/Core/ZtLogger.h"

class ZtWorld : public ZtObject
{
	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtWorld");

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay() override;

	ZtLevel& GetLevel();

protected:

	ZtLevel Level;

};