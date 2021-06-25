#pragma once

#include "ZtObject.h"
#include "ZtLogger.h"

class ZtLevel : public ZtObject
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtLevel");

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay() override;

};