#include "Zinet/Engine/ECS/ZtComponent.h"

namespace zt::engine::ecs
{

	Component::Component(core::UniqueID&& uniqueID)
		: id{ std::move(uniqueID) }
	{

	}

}