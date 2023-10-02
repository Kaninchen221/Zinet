#pragma once 

#include "Zinet/Engine/ZtEngineConfig.h"

#include "Zinet/Engine/ECS/ZtECSTypes.h"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Entity
	{
	public:

		inline static constexpr Types::EntityID InvalidID = std::numeric_limits<Types::EntityID>::max();

		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;

		Entity(Types::EntityID newID) : id{ newID } {}

		Entity& operator = (const Entity& other) = default;
		Entity& operator = (Entity&& other) = default;

		~Entity() noexcept = default;

		Types::EntityID getID() const { return id; }

	protected:

		Types::EntityID id = InvalidID;

	};

};
