#include <type_traits>

template<typename FirstFunctionPointer, typename SecondFunctionPointer>
constexpr const bool IsFunctionEqual([[maybe_unused]] const SecondFunctionPointer& secondFunctionPointer)
{
	return std::is_same<FirstFunctionPointer, SecondFunctionPointer>::value;
}