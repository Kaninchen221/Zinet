#pragma once 

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtECSTypes.h"

#include "Zinet/Core/ZtIDTypes.h"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Entity
	{
	public:

		Entity() = default;
		Entity(core::UniqueID&& uniqueID) : id{ std::move(uniqueID) } {}
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;

		Entity& operator = (const Entity& other) = default;
		Entity& operator = (Entity&& other) = default;

		~Entity() noexcept = default;

		const core::UniqueID& getID() const { return id; }

	protected:

		core::UniqueID id;

	};

};
