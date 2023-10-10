#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Component
	{
	public:
		Component() = default;
		Component(const Component& other) = default;
		Component(Component&& other) = default;
		
		Component& operator = (const Component& other) = default;
		Component& operator = (Component&& other) = default;
		
		~Component() = default;
	
	};

}

