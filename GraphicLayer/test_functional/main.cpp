#include <gtest/gtest.h>


// TODO (low) Create a separate file for that class in zinet core
//#define ZINET_COLLECT_MALLOC_DATA
#ifdef ZINET_COLLECT_MALLOC_DATA

#include <array>
#include "Zinet/Core/ZtDebug.h"

class Statistics
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
	return Statistics::NewPointer(size);
}

void operator delete(void* pointerToFree) noexcept
{
	return Statistics::Delete(pointerToFree);
}

void* operator new[](std::size_t size)
{
	return Statistics::NewPointer(size);
}

void operator delete[](void* pointerToFree) noexcept
{
	return Statistics::Delete(pointerToFree);
}
#endif

int main(int argc, char* argv[]) 
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}