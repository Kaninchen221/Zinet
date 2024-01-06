#pragma once

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/Core/ZtTime.hpp"
#include "Zinet/Core/ZtIDTypes.hpp"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Component
	{
	public:
		Component() = default;
		Component(core::UniqueID&& newUniqueID, core::ID entityID);
		Component(const Component& other) = delete;
		Component(Component&& other) = default;
		
		Component& operator = (const Component& other) = delete;
		Component& operator = (Component&& other) = default;
		
		virtual ~Component() noexcept = default;

		virtual void preUpdate(core::Time elapsedTime) {}

		virtual void update(core::Time elapsedTime) {}

		virtual void postUpdate(core::Time elapsedTime) {}

		const core::UniqueID& getUniqueID() const { return uniqueID; }

		core::ID getOwnerID() const { return ownerEntityID; }

		virtual bool isReadyToUse() const { return true; }

	protected:

		core::UniqueID uniqueID;
		core::ID ownerEntityID;

	};

}

