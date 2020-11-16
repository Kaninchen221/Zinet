#pragma once

#include "Zinet/Main/ZtMainConfig.h"
#include "Zinet/Main/ZtIdentificator.h"

namespace zt {

	class ZINET_MAIN_API Entity {

	public:

		Entity() noexcept = delete;
		Entity(const Entity& other) noexcept = default;
		Entity(Entity&& other) noexcept = default;
		Entity(Identificator identificator) noexcept;

		Entity& operator = (const Entity& other) noexcept = default;
		Entity& operator = (Entity&& other) noexcept = default;

		~Entity() noexcept = default;

		Identificator getIdentificator() const noexcept;

	private:

		Identificator identificator;

	};

}