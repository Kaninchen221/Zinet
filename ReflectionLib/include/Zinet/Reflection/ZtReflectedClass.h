#pragma once

#include "Zinet/Reflection/ZtReflection.h"

namespace zt::reflection
{

	class ZINET_REFLECTION_LAYER_API ReflectedClass
	{

	public:

		ReflectedClass() = default;
		ReflectedClass(const ReflectedClass& other) = default;
		ReflectedClass(ReflectedClass&& other) = default;

		ReflectedClass(std::string_view newName) : name{newName} {}

		ReflectedClass& operator = (const ReflectedClass& other) = default;
		ReflectedClass& operator = (ReflectedClass&& other) = default;

		~ReflectedClass() noexcept = default;

		constexpr std::string_view getName() const { return name; }

	protected:

		std::string_view name;

	};

}