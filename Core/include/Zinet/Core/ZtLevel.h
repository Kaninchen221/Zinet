#pragma once

#include "ZtCore.h"
#include "ZtLogger.h"

class ZINET_CORE_API ZtLevel
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtLevel");

public:

    virtual void BeginPlay();

    virtual void Tick(float DeltaTime);

    virtual void EndPlay();

#ifdef ZINET_DEBUG_UI
    virtual void ImGuiChildren() const;
#endif

};