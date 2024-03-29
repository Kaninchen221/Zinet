#pragma once 

#include "Zinet/Engine/ZtEngineConfig.hpp"

#include "Zinet/Engine/ECS/ZtECSTypes.hpp"

#include "Zinet/Core/ZtIDTypes.hpp"

namespace zt::engine::ecs
{

	class ZINET_ENGINE_API Entity
	{
	public:

		Entity() = default;
		Entity(core::UniqueID&& newUniqueID) : uniqueID{ std::move(newUniqueID) } {}
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;

		Entity& operator = (const Entity& other) = default;
		Entity& operator = (Entity&& other) = default;

		~Entity() noexcept = default;

		const core::UniqueID& getUniqueID() const { return uniqueID; }

	protected:

		core::UniqueID uniqueID;

	};

};
