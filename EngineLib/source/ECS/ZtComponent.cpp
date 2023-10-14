#include "Zinet/Engine/ECS/ZtComponent.h"

namespace zt::engine::ecs
{


	Component::Component(core::UniqueID&& newUniqueID, core::ID entityID)
		: uniqueID{ std::move(newUniqueID) },
		ownerEntityID{ entityID }
	{
	}

}