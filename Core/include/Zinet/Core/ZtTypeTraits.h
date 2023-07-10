#pragma once

#include <type_traits>

namespace zt::core
{

	template<typename FirstFunctionPointer, typename SecondFunctionPointer>
	constexpr const bool IsFunctionEqual([[maybe_unused]] const SecondFunctionPointer& secondFunctionPointer)
	{
		return std::is_same<FirstFunctionPointer, SecondFunctionPointer>::value;
	}

	// TODO (mid) convert it to free function
	inline constexpr const auto LambdaFree = [](void* pointer)
	{
		std::free(pointer);
	};

}