#include "Zinet/Core/ZtEntity.h"

void ZtEntity::AssignUID()
{
	UniqueIdentifier = NextUniqueIdentifier;
	NextUniqueIdentifier++;
}

ZtEntity::ZtEntity()
{
	AssignUID();
}

size_t ZtEntity::GetUID() const
{
	return UniqueIdentifier;
}
