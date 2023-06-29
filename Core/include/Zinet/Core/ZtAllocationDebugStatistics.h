#pragma once

#include <array>

#ifdef ZINET_COLLECT_ALLOCATION_DEBUG_DATA

// TODO (Low) Improve it, collect more data, print some usefull info
// If you want to use it then include it in main.cpp file before any include
class ZinetCollectAllocationDebugData
{
public:

	struct Pointer
	{
		void* rawPointer = nullptr;
		size_t size = 0u;
	};

	static inline std::array<Pointer, 100000> Pointers{ nullptr };

	const static inline constexpr bool GatherData = true;

	static void* NewPointer(std::size_t size)
	{
		if constexpr (GatherData)
		{
			void* newPointer = std::malloc(size);
			for (Pointer& pointer : Pointers)
			{
				if (pointer.rawPointer == nullptr)
				{
					pointer.rawPointer = newPointer;
					pointer.size = size;

					return newPointer;
				}
			}

			return newPointer; // Out of size
		}
		else
			return std::malloc(size);
	}

	static void Delete(void* pointerToFree)
	{
		if constexpr (GatherData)
		{
			for (Pointer& pointer : Pointers)
			{
				if (pointer.rawPointer == pointerToFree)
				{
					pointer = Pointer{};
					std::free(pointerToFree);
					return;
				}
			}

			std::free(pointerToFree); // Not registered pointer
			return;
		}
		else
			std::free(pointerToFree);
	}
};

void* operator new (std::size_t size)
{
	return ZinetCollectAllocationDebugData::NewPointer(size);
}

void operator delete(void* pointerToFree) noexcept
{
	return ZinetCollectAllocationDebugData::Delete(pointerToFree);
}

void* operator new[](std::size_t size)
{
	return ZinetCollectAllocationDebugData::NewPointer(size);
}

void operator delete[](void* pointerToFree) noexcept
{
	return ZinetCollectAllocationDebugData::Delete(pointerToFree);
}

#endif