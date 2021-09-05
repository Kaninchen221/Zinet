#pragma once

#include "Zinet/Core/ZtCore.h"
#include "Zinet/Core/ZtLevel.h"
#include "Zinet/Core/ZtLogger.h"

class ZINET_CORE_API ZtWorld
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtWorld");

public:

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

	virtual void EndPlay();

	ZtLevel& GetLevel();

#ifdef ZINET_DEBUG_UI
    virtual void ImGuiChildren() const;
#endif

protected:

	ZtLevel Level;

};