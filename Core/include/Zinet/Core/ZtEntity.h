#pragma once

#include "Zinet/Core/ZtCore.h"

class ZINET_CORE_API ZtEntity
{

	inline static size_t NextUniqueIdentifier = 0u;

	size_t UniqueIdentifier;

	void AssignUID();

public:

	ZtEntity();

	size_t GetUID() const;

};