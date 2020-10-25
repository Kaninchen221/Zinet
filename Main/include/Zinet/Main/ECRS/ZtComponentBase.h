#pragma once

#include "Zinet/Main/ZtMainConfig.h"

#include <memory>

namespace zt {

	class ComponentBase;

	using ComponentPtr = std::shared_ptr<ComponentBase>;
	using ComponentWeakPtr = std::weak_ptr<ComponentBase>;

	class ZINET_MAIN_API ComponentBase {

	public:

		ComponentBase() = default;
		ComponentBase(const ComponentBase& other);
		ComponentBase(ComponentBase&& other);

		virtual ComponentBase& operator = (const ComponentBase& other) = default;
		virtual ComponentBase& operator = (ComponentBase&& other) = default;

		virtual ComponentPtr getCopy() const = 0;

		virtual ~ComponentBase() noexcept = default;

	};
}