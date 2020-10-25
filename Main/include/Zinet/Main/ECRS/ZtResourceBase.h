#pragma once

#include "Zinet/Main/ZtMainConfig.h"

#include <memory>

namespace zt {

	class ResourceBase;

	using ResourcePtr = std::shared_ptr<ResourceBase>;
	using ResourceWeakPtr = std::weak_ptr<ResourceBase>;

	class ZINET_MAIN_API ResourceBase {

	public:

		ResourceBase() = default;
		ResourceBase(const ResourceBase& other);
		ResourceBase(ResourceBase&& other);

		virtual ResourceBase& operator = (const ResourceBase& other) = default;
		virtual ResourceBase& operator = (ResourceBase&& other) = default;

		virtual ResourcePtr getCopy() const = 0;

		virtual ~ResourceBase() noexcept = default;

	};

}