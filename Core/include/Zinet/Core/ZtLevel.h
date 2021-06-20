#pragma once

#include "ZtObject.h"

class ZtLevel : public ZtObject
{

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay() override;

};