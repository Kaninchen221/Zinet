#pragma once

#include "ZtObject.h"
#include "ZtLogger.h"

class ZtLevel : public ZtObject
{
protected:

	inline static ZtLogger::SimpleConsoleLogger Logger = ZtLogger::CreateSimpleConsoleLogger("ZtLevel");

public:


};