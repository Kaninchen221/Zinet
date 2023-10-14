#pragma once

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Core/ZtTime.h"
#include "Zinet/Core/ZtIDTypes.h"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Component
	{
	public:
		Component() = default;
		Component(core::UniqueID&& uniqueID);
		Component(const Component& other) = default;
		Component(Component&& other) = default;
		
		Component& operator = (const Component& other) = default;
		Component& operator = (Component&& other) = default;
		
		virtual ~Component() = default;
	
		virtual void update(core::Time elapsedTime) {}

		const core::UniqueID& getID() const { return id; }

	protected:

		core::UniqueID id;

	};

}

